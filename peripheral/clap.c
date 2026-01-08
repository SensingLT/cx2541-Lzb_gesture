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
    for(int i = 1; i <= 9; i++) {
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

typedef struct {
    uint8_t count;              // 当前连拍计数
    uint32_t firstPressTick;   // 第一次按键时间
    uint32_t lastPressTick;    // 最后一次按键时间
    bool detecting;             // 是否在检测连拍
    uint8_t lastDetectedKey;    // 最后检测到的按键
} clap_multi_detector_t;

static clap_multi_detector_t multiDetector = {0};

// 连拍检测参数 - 1tick = 10ms
#define MULTI_PRESS_TIMEOUT_TICK   40  // 连拍超时时间（400毫秒）
#define MULTI_PRESS_INTERVAL_TICK  20  // 连拍最小间隔时间（200毫秒）


static void resetMultiPressDetector(void) {
    multiDetector.count = 0;
    multiDetector.detecting = false;
    multiDetector.lastDetectedKey = 0;
}

// 连拍检测函数
static clap_count_e detectMultiPress(uint8_t currentKey, uint32_t currentTick) {
    if (currentKey == 0) {
        // 没有按键，检查是否超时
        if (multiDetector.detecting) {
            uint32_t timeDiff = currentTick - multiDetector.lastPressTick;
            if (timeDiff > MULTI_PRESS_TIMEOUT_TICK) {
                // 超时，返回当前计数
                uint8_t result = multiDetector.count;
                if (result >= 2 && result <= 3) {
                } else if (result > 3) {
                    result = 0; // 超过3次判断为无效
                }
                resetMultiPressDetector();
                return (clap_count_e)result;
            }
        }
        return CLAP_ZERO;
    }
    
    // 有按键按下
    if (!multiDetector.detecting) {
        // 开始新的连拍检测
        multiDetector.count = 1;
        multiDetector.firstPressTick = currentTick;
        multiDetector.lastPressTick = currentTick;
        multiDetector.detecting = true;
        multiDetector.lastDetectedKey = currentKey;
        return CLAP_ZERO;
    } else {
        uint32_t timeDiff = currentTick - multiDetector.lastPressTick;
        
        if (timeDiff < MULTI_PRESS_INTERVAL_TICK) {
            return CLAP_ZERO;
        }
        
        if (timeDiff > MULTI_PRESS_TIMEOUT_TICK) {
            // 超时，重新开始计数
            multiDetector.count = 1;
            multiDetector.firstPressTick = currentTick;
            multiDetector.lastDetectedKey = currentKey;
        } else {
            // 有效连拍，增加计数
            multiDetector.count++;
            multiDetector.lastDetectedKey = currentKey;
        }
        multiDetector.lastPressTick = currentTick;
        return CLAP_ZERO;
    }
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