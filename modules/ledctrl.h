/****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: LED_controller.h
*
* PROJECT....: EMP

* DESCRIPTION: Interface to a LED struct.
*
* Change Log:
*****************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 050128  KA    Module created.
*
*******************************************************************************/

#pragma once

/*****************************    Includes    *********************************/

#include <stdlib.h>

#include "../tm4c123gh6pm.h"
#include "emp_type.h"

#include "driver.h"
#include "tp.h"
#include "led.h"

/*****************************    Defines    **********************************/

typedef struct	LED_CONTROLLER			LED_CONTROLLER;
typedef struct	LED_CONTROLLER_CLASS	LED_CONTROLLER_CLASS;

typedef enum	LEDCTRL_MODE 			LEDCTRL_MODE;


/*************************** MAIN Constructs   ********************************/
extern const struct LED_CONTROLLER_CLASS
{
	LED_CONTROLLER*	(*new)(void);
	void 			(*del)(LED_CONTROLLER* this);

	void 			(*operate)(LED_CONTROLLER* this, LED* led_obj);
	void 			(*set_mode)(LED_CONTROLLER* this, LEDCTRL_MODE mode);

} ledctrl;

/*************************    CONSTRUCTS         ******************************/

enum LEDCTRL_MODE
{
	NORMAL 	  = 0,
	NORWEGIAN = 1,
	EMERGENCY = 2
};

struct LED_CONTROLLER
{
	LEDCTRL_MODE	mode;
	TIMEPOINT*		tp_timer;
};
/***************************** END MODULE    **********************************/
