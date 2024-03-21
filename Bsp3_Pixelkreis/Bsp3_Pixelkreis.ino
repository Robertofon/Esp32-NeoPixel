#include <Adafruit_NeoPixel.h>
#define PIN 2 // Hier wird angegeben, an welchem digitalen Pin die WS2812 LEDs bzw. NeoPixel angeschlossen sind
#define NUMPIXELS 16 // Hier wird die Anzahl der angeschlossenen WS2812 LEDs bzw. NeoPixel angegeben
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

const int PAUSE_MS = 50;

const auto BLACK = pixels.Color(0,0,0);
const auto RED = pixels.Color(128,0,0);
const auto GREEN = pixels.Color(0,128,0);
const auto BLUE = pixels.Color(0,0,128);
const auto YELLOW = pixels.Color(128,128,0);
const auto WHITE = pixels.Color(128,128,128);

const int RED_STEP = 92/NUMPIXELS;
const int RED_MIN = 8;

bool red_up;
int red_value;

void setup(void) {
	pixels.begin();
	
	red_value = RED_MIN;
	red_up = true;
}

void loop() {
	for (int i=0; i<NUMPIXELS; i++) {
		if (red_up) {
			red_value = red_value + RED_STEP;
		}
		else {
			red_value = red_value - RED_STEP;
		}
		
		set_all_pixels(pixels.Color(red_value, 0, 0));
		
		int j = (i+NUMPIXELS/2)%NUMPIXELS;
		pixels.setPixelColor(i, GREEN);
		pixels.setPixelColor(j, BLUE);
		pixels.show();
		
		delay(100);
		set_all_pixels(BLACK);
	}
	
	red_up = !red_up;
}

void show(uint32_t color) {
	set_all_pixels(color);
	pixels.show();
	
	delay(PAUSE_MS);
}

void set_all_pixels(uint32_t color) {
	for (int i=0; i<NUMPIXELS; i++) {
		pixels.setPixelColor(i, color);
	}
}