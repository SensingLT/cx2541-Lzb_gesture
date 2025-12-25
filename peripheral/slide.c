#include "slide.h"
#include "uart.h"
#include "protocol.h"
#include "PT32Y003x.h"

#define SLIDE_SDO_PORT 	GPIOC
#define	SLIDE_SDO_PIN	GPIO_Pin_5

#define SLIDE_SCL_PORT 	GPIOC
#define	SLIDE_SCL_PIN	GPIO_Pin_6

#define SLIDE_SCL_HIGH	GPIO_SetBits(SLIDE_SCL_PORT,SLIDE_SCL_PIN);
#define SLIDE_SCL_LOW	GPIO_ResetBits(SLIDE_SCL_PORT,SLIDE_SCL_PIN);

void slide_init(void){
	//SDO - 输入
	GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_In;
    GPIO_InitStructure.GPIO_Pull = GPIO_Pull_Down;
	GPIO_InitStructure.GPIO_Pin  = SLIDE_SDO_PIN;
    GPIO_Init(SLIDE_SDO_PORT,&GPIO_InitStructure);
	
	//SCL - 输出
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OutPP;
    GPIO_InitStructure.GPIO_Pull = GPIO_Pull_NoPull;
	GPIO_InitStructure.GPIO_Pin  = SLIDE_SCL_PIN;
    GPIO_Init(SLIDE_SCL_PORT,&GPIO_InitStructure);
}

static uint8_t slide_readSDO(void){
	return GPIO_ReadDataBit(SLIDE_SDO_PORT ,SLIDE_SDO_PIN);
}

static uint8_t slide_keyOut(void){
	uint8_t keys = 0;
    static bool keyPressed = false;
    static uint8_t lastKey = 0;
	SLIDE_SCL_HIGH;	
	for(int i = 1;i <= 16; i++){
		SLIDE_SCL_LOW;	
		if(slide_readSDO() == RESET){
			keys = i;
			break;
		}
		SLIDE_SCL_HIGH;
	}
	return keys;
}

// 滑动检测结构体
typedef struct {
    slide_state_e state;
    slide_direction_e direction;
    uint8_t lastKey;
    uint8_t keyCount;
    uint32_t lastKeyTick;
    bool expectingRelease;  // 标记是否期待按键释放
    uint8_t keySequence[8]; // 记录按键序列
} slide_detector_t;

slide_detector_t gSlideDetector;//滑动操作结构体


static void slide_initDetector(slide_detector_t * pSlideDetector){
	pSlideDetector->state = SLIDE_IDLE;
	pSlideDetector->direction = SLIDE_NONE;
	pSlideDetector->keyCount = 0;
	pSlideDetector->lastKey  = 0;
	pSlideDetector->lastKeyTick = 0;

}


const static uint32_t slideTickOut = 50; // 500ms超时
const static uint8_t minSlideKeys = 3; 

// 检查按键序列是否形成有效滑动
static bool slide_checkPattern(slide_detector_t* detector) {
    
    if (detector->keyCount < minSlideKeys) {
		DBG_LN("keys counts is not enough\r\n");
        return false;
    }
    
    // 检查按键序列方向一致性
    int directionSign = (detector->direction == SLIDE_TO_FORWARD) ? 1 : -1;
    int lastKey = detector->keySequence[0];
    
    for (int i = 1; i < detector->keyCount; i++) {
        int currentKey = detector->keySequence[i];
        // 检查按键是否按方向移动
        if ((currentKey - lastKey) * directionSign <= 0) {
			DBG_LN("direction error\r\n");
            return false; // 方向不一致
        }   
        lastKey = currentKey;
    }
    return true;
}

// 检测滑动操作
static bool slide_detectSlide(slide_detector_t* detector, uint8_t currentKey, uint32_t currentTick) {
    
    // 处理按键释放状态
    if (currentKey == 0) {
        if (detector->state == SLIDE_DETECTING && detector->expectingRelease) {
            // 在容忍时间内检测到释放，继续等待下一个按键
            detector->expectingRelease = false;
            return false;
        }
        return false;
    }
    
    // 处理按键按下状态
    if (detector->state == SLIDE_IDLE) {
        // 开始新的检测
        detector->state = SLIDE_DETECTING;
        detector->lastKey = currentKey;
        detector->keyCount = 1;
        detector->keySequence[0] = currentKey;
        detector->lastKeyTick = currentTick;
        detector->expectingRelease = true;
        return false;
    }
    
    if (detector->state == SLIDE_DETECTING) {
        // 忽略重复按键（同一按键多次触发）
        if (currentKey == detector->lastKey) {
            detector->lastKeyTick = currentTick;
			DBG_LN("same key\r\n");
            return false;
        }
        
        // 确定滑动方向
        if (detector->keyCount == 1) {
            detector->direction = (currentKey > detector->lastKey) ? 
                                 SLIDE_TO_FORWARD : 
                                 SLIDE_TO_BACKWARD;
        }
        
        // 检查方向是否一致
        bool directionOk = false;
        if (detector->direction == SLIDE_TO_FORWARD && currentKey > detector->lastKey) {
            directionOk = true;
        } else if (detector->direction == SLIDE_TO_BACKWARD && currentKey < detector->lastKey) {
            directionOk = true;
        }
        
        if (directionOk) {
            // 添加新按键到序列
            detector->keySequence[detector->keyCount] = currentKey;
            detector->keyCount++;
            detector->lastKey = currentKey;
            detector->lastKeyTick = currentTick;
            detector->expectingRelease = true;
            
            // 检查是否形成有效滑动
            if (detector->keyCount >= minSlideKeys && slide_checkPattern(detector)) {
                detector->state = SLIDE_COMPLETE;
                return true;
            }
        } else {
			DBG_LN("init Slide !");
            // 方向不一致，重置
            slide_initDetector(detector);
        }
    }
    
    return false;
}


#define SLIDE_TIMEOUT_TICK    120   // 1200毫秒超时

// 检查超时并重置检测器
static void slide_checkTimeOut(slide_detector_t* detector, uint32_t currentTick) {
    if (detector->state != SLIDE_IDLE && 
        (currentTick - detector->lastKeyTick) >SLIDE_TIMEOUT_TICK) {
        DBG_LN("Slide detection timeout, resetting...\r\n");
        slide_initDetector(detector);
    }
}

//冷却时间相关变量
static bool coolingDown = false;        // 冷却状态标志
static uint32_t coolDownStartTime = 0;  // 冷却开始时间
#define  COOL_DOWN_PERIOD  100  		//1000ms冷却时间
static bool keyPressed = false;  // 按键按下状态标志
static uint8_t lastKey = 0;  // 记录上一次的按键值

//滑动检测任务
void slide_task(void){
	//检查滑动检测超时
	slide_checkTimeOut(&gSlideDetector,  Tick_Get());
	
	//检测冷却时间
	if(coolingDown){
		if(Tick_Get() - coolDownStartTime > COOL_DOWN_PERIOD){
			coolingDown = false;
		}
		else{
			return;
		}
	}
	
	uint8_t slideKey = slide_keyOut();
	if (slideKey != 0) {
		// 有按键按下
		if (!keyPressed || slideKey != lastKey) {
			DBG_LN("Key %d\r\n",slideKey);
			// 新按键按下或按键切换
			if (slide_detectSlide(&gSlideDetector, slideKey, Tick_Get())) {
				DBG_LN("Slide detected! Direction: %s \r\n", 
					  (gSlideDetector.direction == SLIDE_TO_FORWARD) ? 
					  "To Forward" : "To Backward");
				
				for (int i = 0; i < gSlideDetector.keyCount; i++) {
					DBG_LN("Key %d: %d \r\n", i+1, gSlideDetector.keySequence[i]);
				}
				
				if(gSlideDetector.direction == SLIDE_TO_FORWARD){
					//发送向前滑动数据
					reportSlideStatus(SLIDE_TO_FORWARD);
				} else {
					//发送向后滑动数据
					reportSlideStatus(SLIDE_TO_BACKWARD);
				}
				coolingDown = true;
				coolDownStartTime = Tick_Get();
				slide_initDetector(&gSlideDetector);
			}
			keyPressed = true;
			lastKey = slideKey;
		}
	} else {
		// 按键释放
		if (keyPressed) {
			// 发送释放信号给检测器
			slide_detectSlide(&gSlideDetector, 0, Tick_Get());
			keyPressed = false;
			lastKey = 0;
		}
	}
}
