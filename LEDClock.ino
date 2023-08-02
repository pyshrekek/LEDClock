#include <FastLED.h>
#include <TimeLib.h>

#define LED_PIN     6
#define NUM_LEDS    60
#define BRIGHTNESS  10
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 2

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
   Serial.println();

  delay(3000);
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(BRIGHTNESS);

  setTime(1690997043);
}

void loop() {
  // put your main code here, to run repeatedly:
  // Turn the LED on, then pause
  for (int i = 0 ; i < NUM_LEDS ; i++) {
    leds[i] = CRGB::Red;
  }
  FastLED.show();
  delay(1000 / UPDATES_PER_SECOND);
  // Now turn the LED off, then pause
  for (int i = 0 ; i < NUM_LEDS ; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
  delay(1000 / UPDATES_PER_SECOND);
  digitalClockDisplay();
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
