/*
 * speed.h
 *
 *  Created on: Aug 16, 2017
 *      Author: VuHuyHop
 */

#ifndef SPEED_CTL_SPEED_H_
#define SPEED_CTL_SPEED_H_

#define PWM_MOTOR_LEFT_F        PWM1_BASE, PWM_OUT_3
#define PWM_MOTOR_LEFT_B        PWM1_BASE, PWM_OUT_2
#define PWM_MOTOR_RIGHT_F       PWM1_BASE, PWM_OUT_6
#define PWM_MOTOR_RIGHT_B       PWM1_BASE, PWM_OUT_7
#define PWM_FREQUENCY       20000
#define DRV_ENABLE_LEFT_CHN_PERIPHERAL      SYSCTL_PERIPH_GPIOA
#define DRV_ENABLE_RIGHT_CHN_PERIPHERAL     SYSCTL_PERIPH_GPIOF
#define DRV_ENABLE_LEFT_CHN_PORT            GPIO_PORTA_BASE
#define DRV_ENABLE_RIGHT_CHN_PORT           GPIO_PORTF_BASE
#define DRV_ENABLE_LEFT_CHN_PIN_F           GPIO_PIN_4
#define DRV_ENABLE_LEFT_CHN_PIN_B           GPIO_PIN_3

#define DRV_ENABLE_RIGHT_CHN_PIN_F          GPIO_PIN_6
#define DRV_ENABLE_RIGHT_CHN_PIN_B          GPIO_PIN_7
extern void speed_control_init();
extern void speed_enable_Hbridge(bool Enable);
extern void setPWM(uint32_t ulBaseAddr, uint32_t ulTimer, uint32_t ulFrequency, int32_t ucDutyCycle);

#endif /* SPEED_CTL_SPEED_H_ */
