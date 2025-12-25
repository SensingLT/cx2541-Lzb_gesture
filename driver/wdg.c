#include "wdg.h"
#include "PT32Y003x.h"

/**
* @brief IWDG驱动函数
* @param 无
* @retval 无
*/
void Wdg_Init(uint32_t rlv)
{
    WDG_LockCmd(IWDG, DISABLE);	//解锁IWDG寄存器
    WDG_SetReload(IWDG, rlv);   //设置重装载寄存器值
    WDG_ReloadCounter(IWDG);	//喂狗(重载计数器)
    WDG_ResetCmd(IWDG, ENABLE);	//看门狗复位使能
    WDG_Cmd(IWDG, ENABLE);		//使能IWDG
    WDG_LockCmd(IWDG, ENABLE);	//锁住IWDG寄存器
}

/**
* @brief IWDG喂狗函数
* @param 无
* @retval 无
*/
void Wdg_Feed(void)
{
    WDG_LockCmd(IWDG, DISABLE);	//解锁IWDG寄存器
    WDG_ReloadCounter(IWDG);	//喂狗(重载计数器)
    WDG_LockCmd(IWDG, ENABLE);	//锁住IWDG寄存器	
}
