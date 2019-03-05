#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS_LEFT 8
#define NUM_LEDS_RIGHT 8
#define NUM_LEDS_FRONT 8
#define NUM_LEDS_REAR 8

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806, define both DATA_PIN and CLOCK_PIN
#define CAR_LEFT_PIN 7
#define CAR_RIGHT_PIN 6
#define CAR_FRONT_PIN 5
#define CAR_REAR_PIN 4

// Define the array of leds
CRGB leds_left[NUM_LEDS_LEFT];
CRGB leds_right[NUM_LEDS_RIGHT];
CRGB leds_front[NUM_LEDS_FRONT];
CRGB leds_rear[NUM_LEDS_REAR];

void setup() { 
	Serial.begin(57600);
	LEDS.addLeds<NEOPIXEL,CAR_LEFT_PIN>(leds_left,NUM_LEDS_LEFT);
  LEDS.addLeds<NEOPIXEL,CAR_RIGHT_PIN>(leds_right,NUM_LEDS_RIGHT);
  LEDS.addLeds<NEOPIXEL,CAR_FRONT_PIN>(leds_front,NUM_LEDS_FRONT);
  LEDS.addLeds<NEOPIXEL,CAR_REAR_PIN>(leds_rear,NUM_LEDS_REAR);
	LEDS.setBrightness(128);
}

void fadeall()
{ 
  for(int i = 0; i < NUM_LEDS_LEFT; i++) 
  { 
    leds_left[i].fadeToBlackBy(50);
    leds_right[i].fadeToBlackBy(50); 
    //leds_front[i].fadeToBlackBy(50); 
    //leds_rear[i].fadeToBlackBy(50); 
  } 
}

void loop() { 
	// First slide the led in one direction
  int i, j;
	for(i = 0,j = NUM_LEDS_RIGHT-1; i < NUM_LEDS_LEFT && j >= 0; i++, j--) {
		// Set the i'th led to red 
		leds_left[i] = CRGB::Purple;
    leds_right[j] = CRGB::Aqua;
		// Show the leds
		FastLED.show(); 
		// now that we've shown the leds, reset the i'th led to black
		// leds[i] = CRGB::Black;
		fadeall();
		// Wait a little bit before we loop around and do it again
		delay(50);
	}

	// Now go in the other direction.
	for(i = (NUM_LEDS_LEFT)-1, j = 0; i >= 0 && j < NUM_LEDS_RIGHT; i--, j++) {
		// Set the i'th led to red 
		leds_left[i] = CRGB::Aqua;
    leds_right[j] = CRGB::Purple;
		// Show the leds
		FastLED.show();
		// now that we've shown the leds, reset the i'th led to black
		// leds[i] = CRGB::Black;
		fadeall();
		// Wait a little bit before we loop around and do it again
		delay(50);
	}
} //loop()
