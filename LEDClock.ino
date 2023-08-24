#include <FastLED.h>
#include <TimeLib.h>
#include <NewPing.h>

#define LED_PIN 3
#define START_LED 0
#define END_LED 180
#define BRIGHTNESS 32
#define LED_TYPE WS2812
#define COLOR_ORDER GRB
#define NUM_LEDS 180

CRGB leds[NUM_LEDS];

#define NUM_SENSORS 2
#define MAX_DISTANCE 40
int TRIG_PINS[NUM_SENSORS] = { 5, 9 };
int ECHO_PINS[NUM_SENSORS] = { 6, 10 };
NewPing sonar[NUM_SENSORS] = {
  NewPing(TRIG_PINS[0], ECHO_PINS[0], MAX_DISTANCE),
  NewPing(TRIG_PINS[1], ECHO_PINS[1], MAX_DISTANCE)
};
int distances[2];

#define UPDATES_PER_SECOND 10

int secondLEDS[3];
int minuteLEDS[3];
int hourLEDS[3];

void setup() {
  delay(1000);

  Serial.begin(9600);
  Serial.println("START");

  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);

  setTime(1690997043);
}

void loop() {
  distances[0] = sonar[0].ping_cm();
  distances[1] = sonar[1].ping_cm();

  populate(secondLEDS, second() * 3);
  populate(minuteLEDS, minute() * 3);
  populate(hourLEDS, hour() * 3);

  Serial.println("TEST");
  if (distances[0] <= 25) {
    for( int i = 0; i < NUM_LEDS; ++i) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
  }
  else {
  for (int i = START_LED; i < END_LED; i++) {
      if (i == secondLEDS[0] || i == secondLEDS[1] || i == secondLEDS[2]) {
        leds[i] = CRGB::White;
      } else if (i == minuteLEDS[0] || i == minuteLEDS[1] || i == minuteLEDS[2]) {
        leds[i] = CRGB::Red;
      } else if (i == hourLEDS[0] || i == hourLEDS[1] || i == hourLEDS[2]) {
        leds[i] = CRGB::Green;
      } else {
        leds[i] = CRGB::Black;
      }
    
  }
  }

  Serial.println("test");
  Serial.println(distances[0]);
  Serial.println(distances[1]);

  FastLED.show();
  delay(1000 / UPDATES_PER_SECOND);
}



void populate(int array[], int val) {
  array[0] = val - 1;
  array[1] = val;
  array[2] = val + 1;

  for (int i = 0; i < 3; i++) {
    if (array[i] == -1) {
      array[i] = 180;
    } else if (array[i] == 181) {
      array[i] = 0;
    }
  }
}
