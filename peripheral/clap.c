#include "clap.h"
#include "uart.h"
#include "PT32Y003x.h"

#define CLAP_SDO_PORT 	GPIOC
#define	CLAP_SDO_PIN	GPIO_Pin_3

#define CLAP_SCL_PORT 	GPIOC
#define	CLAP_SCL_PIN	GPIO_Pin_4

#define CLAP_SCL_HIGH	GPIO_SetBits(CLAP_SCL_PORT,CLAP_SCL_PIN);
#define CLAP_SCL_LOW	GPIO_ResetBits(CLAP_SCL_PORT,CLAP_SCL_PIN);

void clap_init(void){
	//SDO - 输入
	GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_In;
    GPIO_InitStructure.GPIO_Pull = GPIO_Pull_Up;
	GPIO_InitStructure.GPIO_Pin  = CLAP_SDO_PIN;
    GPIO_Init(CLAP_SDO_PORT,&GPIO_InitStructure);
	
	//SCL - 输出
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OutPP;
    GPIO_InitStructure.GPIO_Pull = GPIO_Pull_NoPull;
	GPIO_InitStructure.GPIO_Pin  = CLAP_SCL_PIN;
    GPIO_Init(CLAP_SCL_PORT,&GPIO_InitStructure);
}

static uint8_t clap_readSDO(void){
	return GPIO_ReadDataBit(CLAP_SDO_PORT ,CLAP_SDO_PIN);
}

static uint8_t clap_keyOut(void) {
    uint8_t keys = 0;
    static bool keyPressed = false;
    static uint8_t lastKey = 0;
    CLAP_SCL_HIGH;    
    for(int i = 1; i <= 8; i++) {
        CLAP_SCL_LOW;    
        if(clap_readSDO() == RESET) {
            keys = i;
			//DBG_LN("KEY %d pressed",keys);
            break;
        }
        CLAP_SCL_HIGH;
    }
    if (keys != 0) {
		// 新按键按下
		if (!keyPressed || keys != lastKey) {
			keyPressed = true;
			lastKey = keys;
			DBG_LN("Key %d pressed, waiting release...", keys);
		}
		return 0; // 按键还未释放，返回0
	} 
	else if (keyPressed) {
		// 按键已释放
		uint8_t releasedKey = lastKey;
		keyPressed = false;
		lastKey = 0;
		DBG_LN("Key %d released", releasedKey);
		return releasedKey;
	}
	return 0; // 无按键状态
}


// 放宽连拍检测参数 - 1tick = 5ms
#define MULTI_PRESS_TIMEOUT_TICK   150  // 连拍超时时间（750毫秒）
#define MULTI_PRESS_INTERVAL_TICK  10  // 连拍最小间隔时间（100毫秒）


typedef struct {
    uint8_t count;              // 当前连拍计数
    uint32_t firstPressTick;   // 第一次按键时间
    uint32_t lastPressTick;    // 最后一次按键时间
    uint8_t lastDetectedKey;   // 最后检测到的按键
    bool active;               // 检测是否活跃
} clap_multi_detector_t;

static clap_multi_detector_t multiDetector = {0};


// 重置检测器
static void resetMultiPressDetector(void) {
    multiDetector.count = 0;
    multiDetector.active = false;
    multiDetector.lastDetectedKey = 0;
}
static clap_count_e detectMultiPress(uint8_t currentKey, uint32_t currentTick) {
    static uint32_t lastReleaseTick = 0;
    static uint8_t pressCount = 0;
    static uint32_t firstPressTick = 0;
    
    if (currentKey != 0) {
        // 按键按下
        if (pressCount == 0) {
            // 第一次按下
            firstPressTick = currentTick;
            pressCount = 1;
            DBG_LN("First press, count=1, key=%d", currentKey);
        } 
        else {
            // 检查是否有效连拍
            uint32_t timeSinceLastPress = currentTick - lastReleaseTick;
            
            if (timeSinceLastPress < MULTI_PRESS_INTERVAL_TICK) {
                // 间隔太短，认为是抖动
                DBG_LN("Press too fast, ignored. Interval: %d ticks", timeSinceLastPress);
                return CLAP_ZERO;
            }
            
            if (timeSinceLastPress > MULTI_PRESS_TIMEOUT_TICK) {
                // 超时，重新开始计数
                DBG_LN("Timeout, reset to 1. Time since last: %d ticks", timeSinceLastPress);
                pressCount = 1;
                firstPressTick = currentTick;
            } 
            else {
                // 有效连拍（允许不同按键）
                pressCount++;
                if (pressCount > CLAP_TRIPLE) {
                    pressCount = CLAP_TRIPLE;
                }
                DBG_LN("Multi-press, count=%d, key=%d", pressCount, currentKey);
            }
        }
        
        // 更新释放时间
        lastReleaseTick = currentTick;
        return CLAP_ZERO;
    } 
    else {
        // 按键释放
        if (pressCount > 0) {
            // 检查是否超时
            uint32_t timeSinceFirstPress = currentTick - firstPressTick;
            
            if (timeSinceFirstPress > MULTI_PRESS_TIMEOUT_TICK) {
                // 拍击完成
                clap_count_e result = (clap_count_e)pressCount;
                if (result > CLAP_TRIPLE) {
                    result = CLAP_TRIPLE;
                }
                
                // 检查是否真的完成（等待一小段时间确认没有新拍击）
                uint32_t timeSinceLastPress = currentTick - lastReleaseTick;
                if (timeSinceLastPress < MULTI_PRESS_INTERVAL_TICK) {
                    // 距离上次按下的时间还太短，再等等
                    DBG_LN("Waiting for more presses...");
                    return CLAP_ZERO;
                }
                
                DBG_LN("Final result: %d, total time: %d ticks", result, timeSinceFirstPress);
                pressCount = 0;
                return result;
            }
        }
    }
    
    return CLAP_ZERO;
}

void clap_task(void){
	/******************连拍逻辑**********************/
	uint8_t clapKey = clap_keyOut();
	uint32_t currentTick = Tick_Get();
	// 检测连拍
	clap_count_e multiPress = detectMultiPress(clapKey, currentTick);
	if(multiPress){
		reportClapStatus(multiPress);
	}
}