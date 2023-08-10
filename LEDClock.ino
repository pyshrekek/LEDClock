#include <FastLED.h>
#include <TimeLib.h>
#include <NewPing.h>

#define LED_PIN     3
#define START_LED   24
#define END_LED     142
#define BRIGHTNESS  32
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
#define CLOCK_SIZE  (END_LED - START_LED + 1)
#define NUM_LEDS    288

CRGB leds[NUM_LEDS];
double ledsPerMinute = CLOCK_SIZE / 60.0;
double ledsPerHour = CLOCK_SIZE / 12.0;

#define NUM_SENSORS 2
#define MAX_DISTANCE 40
int TRIG_PINS[NUM_SENSORS] = {5, 9};
int ECHO_PINS[NUM_SENSORS] = {6, 10};
NewPing sonar[NUM_SENSORS] = {
  NewPing(TRIG_PINS[0], ECHO_PINS[0], MAX_DISTANCE),
  NewPing(TRIG_PINS[1], ECHO_PINS[1], MAX_DISTANCE)
};
int distances[NUM_SENSORS];

#define UPDATES_PER_SECOND 20

void setup() {
  Serial.begin(9600);

  delay(3000);

  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);

  setTime(1690997043);
}

void loop() {
  for (int i = 0 ; i < NUM_SENSORS ; i++) {
    distances[i] = sonar[i].ping_cm();
  }
  Serial.println(distances[0]);
  Serial.println(distances[1]);

  int minLed = int(30 * ledsPerMinute) % CLOCK_SIZE + START_LED;
  int hourLed = int((3 * ledsPerHour)) % CLOCK_SIZE + START_LED;
  
  if(distances[0] <= 20 || distances[1] <= 20) {
    for(int i = START_LED; i <= END_LED; i++) {
      if(i == minLed) {
        leds[i] = CRGB::Green;
      }else if (i == hourLed) {
        leds[i] = CRGB::Purple;
      }else {
        leds[i] = CRGB::Black;
      }
    }
  }else {
    for(int i = START_LED; i <= END_LED; i++) {
      leds[i] = CRGB::Black;
    }
  }

  leds[END_LED] = CRGB::Red;
  leds[START_LED] = CRGB::Blue;
  // Serial.println(minute());
  

  FastLED.show();
  delay(1000 / UPDATES_PER_SECOND);
}

void digitalClockDisplay(){
   // digital clock display of the time
   Serial.print(hour());
   printDigits(minute());
   printDigits(second());
   Serial.print(" ");
   Serial.print(day());
   Serial.print(" ");
   Serial.print(month());
   Serial.print(" ");
   Serial.print(year());
   Serial.println();
}

void printDigits(int digits) {
   // utility function for digital clock display: prints preceding colon and leading 0
   Serial.print(":");
   if(digits < 10)
      Serial.print('0');
      Serial.print(digits);
}
