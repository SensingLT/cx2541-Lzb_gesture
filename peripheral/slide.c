#include "slide.h"
#include "uart.h"
#include "string.h"
#include "protocol.h"
#include "PT32Y003x.h"


// 滑动检测结构体
typedef struct {
    slide_state_e state;
    slide_direction_e direction;
    uint8_t lastKey;
    uint8_t keyCount;
    uint32_t lastKeyTick;
    uint8_t keySequence[5]; 
} slide_detector_t;

slide_detector_t gSlideDetector;  // 滑动操作结构体


static void slide_initDetector(slide_detector_t * pSlideDetector){
    pSlideDetector->state = SLIDE_IDLE;
    pSlideDetector->direction = SLIDE_NONE;
    pSlideDetector->lastKey = 0;
    pSlideDetector->keyCount = 0;
    pSlideDetector->lastKeyTick = 0;
    memset(pSlideDetector->keySequence, 0, sizeof(pSlideDetector->keySequence));
}

#define SLIDE_SDO_PORT 	GPIOC
#define	SLIDE_SDO_PIN	GPIO_Pin_3

#define SLIDE_SCL_PORT 	GPIOC
#define	SLIDE_SCL_PIN	GPIO_Pin_4

#define SLIDE_SCL_HIGH	GPIO_SetBits(SLIDE_SCL_PORT,SLIDE_SCL_PIN);
#define SLIDE_SCL_LOW	GPIO_ResetBits(SLIDE_SCL_PORT,SLIDE_SCL_PIN);

void slide_init(void){
	//SDO - 输入
	GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_In;
    GPIO_InitStructure.GPIO_Pull = GPIO_Pull_Up;
	GPIO_InitStructure.GPIO_Pin  = SLIDE_SDO_PIN;
    GPIO_Init(SLIDE_SDO_PORT,&GPIO_InitStructure);
	
	//SCL - 输出
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OutPP;
    GPIO_InitStructure.GPIO_Pull = GPIO_Pull_NoPull;
	GPIO_InitStructure.GPIO_Pin  = SLIDE_SCL_PIN;
    GPIO_Init(SLIDE_SCL_PORT,&GPIO_InitStructure);
	GPIO_SetBits(SLIDE_SCL_PORT,SLIDE_SCL_PIN);
    
    // 初始化滑动检测器
    slide_initDetector(&gSlideDetector);
}

static uint8_t slide_readSDO(void){
	return GPIO_ReadDataBit(SLIDE_SDO_PORT ,SLIDE_SDO_PIN);
}

static uint8_t slide_keyOut(void){
	uint8_t keys = 0;
	SLIDE_SCL_HIGH;	
	for(int i = 1;i <= 16; i++){
		SLIDE_SCL_LOW;	
		if(slide_readSDO() == RESET){
			keys = i;
		}
		SLIDE_SCL_HIGH;
	}
	return keys;
}

const static uint8_t minSlideKeys = 3; 
// 检查按键序列是否形成有效滑动
static bool slide_checkPattern(slide_detector_t* detector) {
    
    if (detector->keyCount < minSlideKeys) {
        return false;
    }
    return true;
}

// 检测滑动操作
static bool slide_detectSlide(slide_detector_t* detector, uint8_t currentKey, uint32_t currentTick) {
    if (currentKey == 0) {
        detector->lastKeyTick = currentTick;
        return false;
    }

    switch(detector->state) {
        case SLIDE_IDLE:
        case SLIDE_COMPLETE:
            detector->state = SLIDE_DETECTING;
            detector->lastKey = currentKey;
            detector->keyCount = 1;
            detector->keySequence[0] = currentKey;
            detector->lastKeyTick = currentTick;
            detector->direction = SLIDE_NONE;
            return false;

        case SLIDE_DETECTING:
            if (currentKey == detector->lastKey) {
                detector->lastKeyTick = currentTick;
                return false;
            }

            // 首次确定方向
            if (detector->direction == SLIDE_NONE) {
                detector->direction = (currentKey > detector->lastKey) ? SLIDE_TO_FORWARD : SLIDE_TO_BACKWARD;
            }

            // 方向校验
            bool directionOk = false;
            if (detector->direction == SLIDE_TO_FORWARD && currentKey > detector->lastKey) directionOk = true;
            else if (detector->direction == SLIDE_TO_BACKWARD && currentKey < detector->lastKey) directionOk = true;

            if (directionOk) {
                // 记录按键序列
                if (detector->keyCount < 8) {
                    detector->keySequence[detector->keyCount++] = currentKey;
                }
                detector->lastKey = currentKey;
                detector->lastKeyTick = currentTick;

                // 满足条件，触发滑动
                if (slide_checkPattern(detector)) {
                    detector->state = SLIDE_COMPLETE;
                    return true;
                }
            } else {
                // 方向错误，重置
                slide_initDetector(detector);
            }
            break;

        default:
            slide_initDetector(detector);
            break;
    }
    return false;
}

#define SLIDE_TIMEOUT_TICK    300   // 1500毫秒超时

// 检查超时并重置检测器
static void slide_checkTimeOut(slide_detector_t* detector, uint32_t currentTick) {
    if (detector->state != SLIDE_IDLE && 
        (currentTick - detector->lastKeyTick) > SLIDE_TIMEOUT_TICK) {
        slide_initDetector(detector);
    }
}

#define COOL_DOWN_PERIOD  200// 1000ms冷却时间

// 声明为static，防止外部访问
static bool coolingDown = false;
static uint32_t coolDownStartTime = 0;
static bool keyPressed = false;
static uint8_t lastKey = 0;

// 防卡死保护
static void slide_antiStuckCheck(void) {
    static uint32_t lastCheckTick = 0;
    static uint32_t lastStateChangeTick = 0;
    static slide_state_e lastState = SLIDE_IDLE;

    uint32_t currentTick = Tick_Get();
    if (currentTick - lastCheckTick >= 100) {
        lastCheckTick = currentTick;

        if (gSlideDetector.state != lastState) {
            lastState = gSlideDetector.state;
            lastStateChangeTick = currentTick;
        }

        // 1秒卡死强制重置
        if (gSlideDetector.state != SLIDE_IDLE && (currentTick - lastStateChangeTick) > 200) {
            slide_initDetector(&gSlideDetector);
            keyPressed = false;
            lastKey = 0;
            coolingDown = false; // 同步重置冷却
        }
    }
}

//滑动检测任务
void slide_task(void){
    slide_antiStuckCheck();
    slide_checkTimeOut(&gSlideDetector, Tick_Get());
    
    // 检测冷却时间
    if(coolingDown){
        if(Tick_Get() - coolDownStartTime > COOL_DOWN_PERIOD){
            coolingDown = false;
            // 冷却结束后，重置所有状态
            keyPressed = false;
            lastKey = 0;
        } else {
            return;
        }
    }
    
    uint8_t slideKey = slide_keyOut();
    
    if (slideKey != 0) {
        // 有按键按下
        if (!keyPressed || slideKey != lastKey) {
           // DBG_LN("Key %d, state=%d, count=%d", slideKey, gSlideDetector.state, gSlideDetector.keyCount);
            
            // 新按键按下或按键切换
            if (slide_detectSlide(&gSlideDetector, slideKey, Tick_Get())) {
                DBG_LN("Slide detected! Direction: %s", 
                      (gSlideDetector.direction == SLIDE_TO_FORWARD) ? 
                      "Forward" : "Backward");
                
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