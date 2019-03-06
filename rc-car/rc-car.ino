/** 
 * The purpose of this program is to implement a "RC Effects" device which allows
 * users to easily perform lighting and audio animation on an rc car.
 * 
 * Author: Juan Caraballo
 * Created: 3/4/2019
 * Copyright 2019, Juan Caraballo, All rights reserved.
 * 
 * Description: The purpose of this program is to implement a "RC Effects" 
 * device which allows users to easily perform lighting and audio animation on
 * an rc car.
 * 
*/

#include <FastLED.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <task.h>

// How many leds in your strip?
#define NUM_LED_PER_STRIP 8

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806, define both DATA_PIN and CLOCK_PIN
#define CAR_LEFT_PIN 7
#define CAR_RIGHT_PIN 6
#define CAR_FRONT_PIN 5
#define CAR_REAR_PIN 4

// Define the arrays of leds
CRGB leds_left[NUM_LED_PER_STRIP];
CRGB leds_right[NUM_LED_PER_STRIP];
CRGB leds_front[NUM_LED_PER_STRIP];
CRGB leds_rear[NUM_LED_PER_STRIP];

/* RTOS Dependent Globals */
TaskHandle_t xAnimateHandle;

/* Function Prototypes */
void AnimationTask(void *pvParameters __attribute__((unused)));

/* Functional Code */
void setup() { 
	Serial.begin(57600);
	LEDS.addLeds<NEOPIXEL,CAR_LEFT_PIN>(leds_left,NUM_LED_PER_STRIP);
  LEDS.addLeds<NEOPIXEL,CAR_RIGHT_PIN>(leds_right,NUM_LED_PER_STRIP);
  LEDS.addLeds<NEOPIXEL,CAR_FRONT_PIN>(leds_front,NUM_LED_PER_STRIP);
  LEDS.addLeds<NEOPIXEL,CAR_REAR_PIN>(leds_rear,NUM_LED_PER_STRIP);
	LEDS.setBrightness(128);

	//Configure RTOS Tasks
	xTaskCreate(
		AnimationTask,
    (const portCHAR *)"Animation Handler",
    128, //stack size
    NULL,
    1, //priority
    &xAnimateHandle
	);
}

void fadeall()
{ 
  for(int i = 0; i < NUM_LED_PER_STRIP; i++) 
  { 
    leds_left[i].fadeToBlackBy(50);
    leds_right[i].fadeToBlackBy(50); 
    leds_front[i].fadeToBlackBy(50); 
    leds_rear[i].fadeToBlackBy(50); 
  } 
}

void loop()
{
	//all work is done within RTOS tasks
}

/* RTOS Tasks */
void AnimationTask(void *pvParameters __attribute__((unused)))
{
	(void) pvParameters;

	while(1) //a task shall never exit or return
	{
		/*Beginning of single animation*/
		//Note the whole point of setting comments for this is just to emphasize that
		//this task will need to become more versatile in time to accept programming
		//from externally connected devices. For now I may just have one or more
		//animations that execute depdending on a set switch variable.
		
		// First slide the leds in one direction
  	int i, j; //i and j trigger opposite flowing animation (note the counter)
		for(i = 0,j = NUM_LED_PER_STRIP-1; i < NUM_LED_PER_STRIP && j >= 0; i++, j--)
		{
			//set colors
			leds_left[i] = CRGB::Purple;
			leds_right[j] = CRGB::Aqua;
			leds_front[i] = CRGB::Purple;
			leds_rear[j] = CRGB::Aqua;
			// Show the leds
			FastLED.show(); 
			// start fading the leds
			fadeall();
			// Wait a little bit before we loop around and do it again
			delay(50);
		}

		// Now slide them in the other direction.
		for(i = (NUM_LED_PER_STRIP)-1, j = 0; i >= 0 && j < NUM_LED_PER_STRIP; i--, j++)
		{
			// Set colors
			leds_left[i] = CRGB::Aqua;
			leds_right[j] = CRGB::Purple;
			leds_front[i] = CRGB::Aqua;
			leds_rear[j] = CRGB::Purple;
			// Show the leds
			FastLED.show();
			// start fading the leds
			fadeall();
			// Wait a little bit before we loop around and do it again
			delay(50);
		}
		
		/*End of single animation*/
	}
}