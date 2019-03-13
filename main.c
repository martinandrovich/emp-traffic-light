#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "driver.h"
#include "tp.h"
#include "btn.h"
#include "led.h"

/*****************************    Defines    *******************************/

#define LAMBDA(c_) ({ c_ _;})

/*****************************   Constants   *******************************/

#define SYSTICK_DUR_MS 1

/*****************************   Variables   *******************************/

/************************    External Methods    ***************************/

extern void tp_test(void);

/************************   Interrupt Handlers   ***************************/

void ISR_SYSTICK(void)
{
    tp.systick();
}

/*******************************   Main   **********************************/

int main(void)
{

    // disable interrupts
    __disable_irq();

    // init SYSTICK
    tp.init_systick(SYSTICK_DUR_MS, ms);
    sys_tick_init(SYSTICK_DUR_MS);

    // enable interrupts
    __enable_irq();

    // init LED instance
    LED* led_1 = led.new();

    led.set_color(led_1, (RGB){0, 1, 0});
    led.set_state(led_1, 1);

    // init BUTTON instance (SW1)
    BUTTON* btn_sw1 = btn.new(SW1);


    // set single press callback to invert LED color
    btn.set_callback(btn_sw1, SINGLE_PRESS, LAMBDA(void _(void)
    		{
    			led.invert_colors(led_1);
    		}
    ));

	// super-loop
	for(;;)
	{
		btn.controller(btn_sw1);
	}

	return 0;
}
