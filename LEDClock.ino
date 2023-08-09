#include <FastLED.h>
#include <TimeLib.h>

#define LED_PIN     6
#define START_LED   24
#define END_LED     142
#define BRIGHTNESS  32
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
#define NUM_LEDS END_LED - START_LED + 1

CRGB leds[NUM_LEDS];



int ledsPerMinute = (NUM_LEDS) / 60;
int ledsPerHour = (NUM_LEDS) / 12;

#define UPDATES_PER_SECOND 1

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
   Serial.println();

  delay(3000);
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);

  setTime(1690997043);
}

void loop() {
  // put your main code here, to run repeatedly:
  // Turn the LED on, then pause
  // for (int i = 0 ; i < NUM_LEDS ; i++) {
  //   if (i == second()) {
  //     leds[i] = CRGB::Blue;
  //   }
  //   else if (i == minute()) {
  //     leds[i] = CRGB::White;
  //   } else if (i == hour() * 5) {
  //     leds[i] = CRGB::Green;
  //   }
  //   else {
  //     leds[i] = CRGB::Black;
  //   }
  // }
  int minLed = int(minute() * ledsPerMinute) % NUM_LEDS + START_LED;
  int hourLed = int(hour() * ledsPerHour) % NUM_LEDS + START_LED;

  for(int i = START_LED; i <= END_LED; i++) {
    if(i == minLed || i == hourLed) {
      leds[i] = CRGB::White;
    }else {
      leds[i] = CRGB::Black;
    }
  }
  Serial.print("daniel haokun patosai steven xu");
  Serial.print(hour());
  Serial.print(hourLed);
  Serial.print(minLed);
  

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
