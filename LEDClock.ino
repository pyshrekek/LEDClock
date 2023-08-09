#include <FastLED.h>
#include <TimeLib.h>
#include <NewPing.h>

#define LED_PIN     6
#define START_LED   24
#define END_LED     142
#define TRIG_PIN    9
#define ECHO_PIN    10
#define BRIGHTNESS  32
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
#define CLOCK_SIZE  (END_LED - START_LED + 1)
#define NUM_LEDS    288
#define MAX_DIST    400

CRGB leds[NUM_LEDS];

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DIST);



double ledsPerMinute = CLOCK_SIZE / 60.0;
double ledsPerHour = CLOCK_SIZE / 12.0;

#define UPDATES_PER_SECOND 1

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

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
  int minLed = int(30 * ledsPerMinute) % CLOCK_SIZE + START_LED;
  int hourLed = int((3 * ledsPerHour)) % CLOCK_SIZE + START_LED;

  int distance = sonar.ping_cm();
  Serial.println(distance);
  
  if(distance <= 20) {
    Serial.println("on");
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
  Serial.println(minute());
  

  FastLED.show();
  // digitalClockDisplay();
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
