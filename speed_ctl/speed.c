/*
 * speed.c
 *
 *  Created on: Aug 16, 2017
 *      Author: VuHuyHop
 */
#include "../include.h"
#include "speed.h"
uint32_t ui32Load;
uint32_t ui32PWMClock;
//private function
static void pwm_init(void);
void speed_control_init (void)
{
    pwm_init();
    setPWM(DRV_ENABLE_LEFT_CHN_PORT, DRV_ENABLE_LEFT_CHN_PIN_F, PWM_FREQUENCY, 0);
    setPWM(DRV_ENABLE_RIGHT_CHN_PORT, DRV_ENABLE_RIGHT_CHN_PIN_F, PWM_FREQUENCY,0);
}
static void pwm_init(void)
{
        SysCtlPWMClockSet(SYSCTL_PWMDIV_1);             // PWM Clock = SystemCLK/1
        SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);        // PWM Channel: PA6,7
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);        //PWM Chanel: PF2,PF3
        // PWM Configuration
        ui32PWMClock = 80000000;    // Calculate PWM clock
        ui32Load = (ui32PWMClock / PWM_FREQUENCY) - 1;

        // 4 PWM channels: PA6, PA7 PF2,PF3(module 1, generator 1,3)
        GPIOPinTypePWM(GPIO_PORTA_BASE, GPIO_PIN_6);
        GPIOPinTypePWM(GPIO_PORTA_BASE, GPIO_PIN_7);

        GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_2);
        GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_3);
        GPIOPinConfigure(GPIO_PA6_M1PWM2);
        GPIOPinConfigure(GPIO_PA7_M1PWM3);
        GPIOPinConfigure(GPIO_PF2_M1PWM6);
        GPIOPinConfigure(GPIO_PF3_M1PWM7);

        PWMGenConfigure(PWM1_BASE, PWM_GEN_1, PWM_GEN_MODE_DOWN|PWM_GEN_MODE_DB_NO_SYNC);
        PWMGenPeriodSet(PWM1_BASE, PWM_GEN_1, ui32Load);
        PWMGenConfigure(PWM1_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN|PWM_GEN_MODE_DB_NO_SYNC);
        PWMGenPeriodSet(PWM1_BASE, PWM_GEN_3, ui32Load);

        PWMOutputState(PWM1_BASE, PWM_OUT_2_BIT, true);
        PWMOutputState(PWM1_BASE, PWM_OUT_3_BIT, true);
        PWMOutputState(PWM1_BASE, PWM_OUT_6_BIT, true);
        PWMOutputState(PWM1_BASE, PWM_OUT_7_BIT, true);

        PWMGenEnable(PWM1_BASE, PWM_GEN_1);
        PWMGenEnable(PWM1_BASE, PWM_GEN_3);
        //======================================//

        ROM_SysCtlPeripheralEnable(DRV_ENABLE_LEFT_CHN_PERIPHERAL);
        ROM_SysCtlPeripheralEnable(DRV_ENABLE_RIGHT_CHN_PERIPHERAL);
        ROM_GPIOPinTypeGPIOOutput(DRV_ENABLE_LEFT_CHN_PORT, DRV_ENABLE_LEFT_CHN_PIN_F|DRV_ENABLE_LEFT_CHN_PIN_B);
        ROM_GPIOPinTypeGPIOOutput(DRV_ENABLE_RIGHT_CHN_PORT, DRV_ENABLE_RIGHT_CHN_PIN_F|DRV_ENABLE_RIGHT_CHN_PIN_B);
        ROM_GPIOPinWrite(DRV_ENABLE_LEFT_CHN_PORT, DRV_ENABLE_LEFT_CHN_PIN_F|DRV_ENABLE_LEFT_CHN_PIN_B, 0);
        ROM_GPIOPinWrite(DRV_ENABLE_RIGHT_CHN_PORT, DRV_ENABLE_RIGHT_CHN_PIN_F|DRV_ENABLE_RIGHT_CHN_PIN_B, 0);
}
void speed_enable_Hbridge(bool Enable)
{
    if (Enable)
    {
        ROM_GPIOPinWrite(DRV_ENABLE_LEFT_CHN_PORT, DRV_ENABLE_LEFT_CHN_PIN_F, DRV_ENABLE_LEFT_CHN_PIN_F);
        ROM_GPIOPinWrite(DRV_ENABLE_LEFT_CHN_PORT, DRV_ENABLE_LEFT_CHN_PIN_B, 0);
        ROM_GPIOPinWrite(DRV_ENABLE_RIGHT_CHN_PORT, DRV_ENABLE_RIGHT_CHN_PIN_F, DRV_ENABLE_RIGHT_CHN_PIN_F);
        ROM_GPIOPinWrite(DRV_ENABLE_RIGHT_CHN_PORT, DRV_ENABLE_RIGHT_CHN_PIN_B, 0);
    }
    else
    {
        ROM_GPIOPinWrite(DRV_ENABLE_LEFT_CHN_PORT, DRV_ENABLE_LEFT_CHN_PIN_F|DRV_ENABLE_LEFT_CHN_PIN_B, 0);
        ROM_GPIOPinWrite(DRV_ENABLE_RIGHT_CHN_PORT, DRV_ENABLE_RIGHT_CHN_PIN_F|DRV_ENABLE_RIGHT_CHN_PIN_B, 0);
    }
}

void setPWM(uint32_t ulBaseAddr, uint32_t ulTimer, uint32_t ulFrequency, int32_t ucDutyCycle)
{
    if (ucDutyCycle > 90)
        ucDutyCycle = 90;
    else if (ucDutyCycle < -90)
        ucDutyCycle = -90;
    PWMPulseWidthSet(ulBaseAddr, ulTimer, (100 + ucDutyCycle) * ui32Load / 200);
}

