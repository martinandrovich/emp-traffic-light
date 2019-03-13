/****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: LED_controller.c
*
* PROJECT....: emp-blinker

* DESCRIPTION: Interface to a LED struct.
*
* Change Log:
*****************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 050128  DT    Module created.
*
****************************************************************************/

/***************************** Include files *******************************/

#include "ledctrl.h"

/*****************************    Defines    *******************************/

#define MAXLED      7
#define MINLED      0

/********************** External declaration of Variables ******************/

extern TIMEPOINT* tp_global;

/*****************************   Constants   *******************************/

#define BLINK_DUR_MS 200

/************************  Function declarations ***************************/

static LED_CONTROLLER*	LED_CONTROLLER_new(void);
static void 			LED_CONTROLLER_del(LED_CONTROLLER* this);

static void 			LED_CONTROLLER_operate(LED_CONTROLLER* this, LED* led_obj);
static void 			LED_CONTROLLER_set_mode(LED_CONTROLLER* this, LEDCTRL_MODE mode);

static void 			_LED_CONTROLLER_mode_normal(LED_CONTROLLER* this, LED* led_obj);
static void 			_LED_CONTROLLER_mode_norwegian(LED_CONTROLLER* this, LED* led_obj);
static void 			_LED_CONTROLLER_mode_emergency(LED_CONTROLLER* this, LED* led_obj);

/****************************   Class Struct   *****************************/

const struct LED_CONTROLLER_CLASS ledctrl =
{
	.new                =  &LED_CONTROLLER_new,
	.del                =  &LED_CONTROLLER_del,

	.operate 	        =  &LED_CONTROLLER_operate,
	.set_mode           =  &LED_CONTROLLER_set_mode
};

/***********************   Constructive Functions   ************************/

static LED_CONTROLLER* LED_CONTROLLER_new(void)
/****************************************************************************
*   Input    : no input, constructor
*   Output   : object pointer
*   Function : creates object
****************************************************************************/
{
	// allocate memory
	LED_CONTROLLER* this = malloc(sizeof(LED_CONTROLLER));

	this->mode			= NORMAL;

	this->tp_timer		= tp.new();

	return this;
}

static void LED_CONTROLLER_del(LED_CONTROLLER* this)
/****************************************************************************
*   Input    : this object
*   Function : deletes object
****************************************************************************/
{
	free(this);
}

/*****************************   Functions   *******************************/

static void LED_CONTROLLER_operate(LED_CONTROLLER* this, LED* led_obj)
/****************************************************************************
*   Input    : Duration
*   Function : LED controller, chooses state
****************************************************************************/
{
	switch ( this->mode ) {

		case NORMAL:
			_LED_CONTROLLER_mode_normal(this, led_obj);
			break;

		case NORWEGIAN :
			_LED_CONTROLLER_mode_norwegian(this, led_obj);
			break;

		case EMERGENCY :
			_LED_CONTROLLER_mode_emergency(this, led_obj);
			break;

		default :
			this->mode = NORMAL;
			break;

	}
}

static void LED_CONTROLLER_callback(LED_CONTROLLER* this, INT32S duration_ms)
/****************************************************************************
*   Input    : Duration
*   Function : LED controller, chooses state
****************************************************************************/
{
	switch (duration_ms)
	{
		case -1:
			this->direction = (this->direction == UP) ? DOWN : UP;
			break;
		// ^-- change mode if double click -- toggle -- does not change anything
		default:
			this->mode = (this->reference_ms > duration_ms) ? MANUAL : AUTO;
			// if normal mode change
			if(this->mode == MANUAL)
			{
				_LED_CONTROLLER_circulation(this);
			}
			else
			{
				__disable_irq();
				tp.copy(this->tp_pressed, tp_global);
				__enable_irq();
			}
			break;
		// -- change mode if AUTO otherwise change to NORMAL and calculate new led.
	};
}

static void LED_CONTROLLER_set_mode(LED_CONTROLLER* this, LEDCTRL_MODE mode)
/****************************************************************************
*   Input    : this and the mode u want to set
*   Function : set mode in this object
****************************************************************************/
{
	this->mode = mode;
}

static void _LED_CONTROLLER_circulation(LED_CONTROLLER* this)
/****************************************************************************
*   Input    : this object
*   Function : update led_color
****************************************************************************/
{
	INT8U alias_state = this->led_color;

	if(this->direction == UP)
	{
		alias_state += 1;
		this->led_color = (this->led_color == MAXLED) ? MINLED : alias_state;
	}
	else
	{
		alias_state -= 1;
		this->led_color = (this->led_color == MINLED) ? MAXLED : alias_state;
	}
}

/****************************** End Of Module ******************************/
