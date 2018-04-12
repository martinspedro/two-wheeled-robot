/* 
 * File:   pwm.h
 * Author: martinspedro
 *
 * Created on April 8, 2018, 12:06 PM
 */

#ifndef PWM_H
#define	PWM_H

#ifdef	__cplusplus
extern "C" {
#endif

void PWM_init();
void PWM_enable();
void set_duty_cycle(uint16_t duty);

#ifdef	__cplusplus
}
#endif

#endif	/* PWM_H */

