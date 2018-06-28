#ifndef __PWM_IN
#define __PWM_IN

#include <typedef.h>

void pwm_in_init(void);

void tim5_irq_init(void);

void tim4_irq_init(void);

void tim5_gpio_init(void);

void tim4_gpio_init(void);

void tim5_capture_init(void);

void tim4_capture_init(void);

#endif
