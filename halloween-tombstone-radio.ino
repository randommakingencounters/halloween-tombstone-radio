// includes
#include <SoftwareSerial.h>
#include "Adafruit_Soundboard.h"

//soundboard pin definitions
#define SFX_TX 5
#define SFX_RX 6
#define SFX_RST 4

// software serial
SoftwareSerial ss = SoftwareSerial(SFX_TX, SFX_RX);
Adafruit_Soundboard sfx = Adafruit_Soundboard(&ss, NULL, SFX_RST);

// global variables
uint8_t randomTrack;
int previousTrack = 7;
int trackPlaying;
unsigned long trackOnTime;
// track duration ms
unsigned long trackDuration;

class ledFlasher
{
    int ledPin;
    long OnTime;
    long OffTime;
    int MaxRand;
    int LedSwitch;
    int ledState;
    unsigned long previousMillis;

  public:
    ledFlasher(int pin, long on, long off, int mrand, int ledtoggle)
    {
      ledPin = pin;
      pinMode(ledPin, OUTPUT);

      OnTime = on;
      OffTime = off;
      MaxRand = mrand;
      LedSwitch = ledtoggle;

      ledState = LOW;
      previousMillis = 0;
    }
    void toggleLed (int pin, long on, long off, int mrand, int ledtoggle)
    {
      this->ledPin = pin;
      this->OnTime = on;
      this->OffTime = off;
      this->MaxRand = mrand;
      this->LedSwitch = ledtoggle;
    }
    void Update()
    {
      // check to see if it's time to change the state of the LED
      unsigned long currentMillis = millis();
      if (LedSwitch == 0) {
        digitalWrite(ledPin, LOW);
      }
      else if ((ledState == HIGH) && (currentMillis - previousMillis >= (OnTime - random(0, MaxRand))))
      {
        ledState = LOW;
        previousMillis = currentMillis;
        digitalWrite(ledPin, ledState);
      }
      else if ((ledState == LOW) && (currentMillis - previousMillis >= (OffTime - random(0, MaxRand))))
      {
        ledState = HIGH;  // turn it on
        previousMillis = currentMillis;   // Remember the time
        digitalWrite(ledPin, ledState);   // Update the actual LED
      }
    }
};

// short circuit led object
ledFlasher led1(9, 500, 800, 800, 0);
ledFlasher led2(10, 750, 1000, 1000, 0);

// front panel led objects
ledFlasher led3(11, 50, 125, 50, 1); // red
ledFlasher led4(12, 150, 275, 100, 1); // green
ledFlasher led5(13, 50, 125, 50, 1); // red

void setup()
{
  // open serial connection to soundboard
  ss.begin(9600);
  randomSeed(analogRead(0));
}

void loop()
{
  // blink leds
  led1.Update();
  led2.Update();
  led3.Update();
  led4.Update();
  led5.Update();

  // loop throught the tracks
  unsigned long currentMillis = millis();
  // track 0
  if ((trackPlaying == 1) && (randomTrack == 0)) {
    // set track duration
    trackDuration = 8312;
    // set leds to static
    led1.toggleLed(9, 500, 800, 800, 1);
    led2.toggleLed(10, 750, 1000, 1000, 1);
    led3.toggleLed(11, 500, 800, 800, 1);
    led4.toggleLed(12, 750, 1000, 1000, 1);
    led5.toggleLed(13, 500, 800, 800, 1);
    if (currentMillis - trackOnTime >= trackDuration) {
      sfx.stop();
      // reset the leds
      led1.toggleLed(9, 0, 0, 0, 0);
      led2.toggleLed(10, 0, 0, 0, 0);
      led3.toggleLed(11, 50, 125, 50, 1);
      led4.toggleLed(12, 150, 275, 100, 1);
      led5.toggleLed(13, 50, 125, 50, 1);
      trackPlaying = 0;
    }
  }
  // track 1
  else if ((trackPlaying == 1) && (randomTrack == 1)) {
    // set track duration
    trackDuration = 30730;
    if (currentMillis - trackOnTime >= trackDuration) {
      sfx.stop();
      trackPlaying = 0;
    }
  }
  // track 2
  else if ((trackPlaying == 1) && (randomTrack == 2)) {
    // get track duration
    trackDuration = 196440;
    if (currentMillis - trackOnTime >= trackDuration) {
      sfx.stop();
      trackPlaying = 0;
    }
  }
  // track 03
  else if ((trackPlaying == 1) && (randomTrack == 3)) {
    // get track duration
    trackDuration = 181211;
    if (currentMillis - trackOnTime >= trackDuration) {
      sfx.stop();
      trackPlaying = 0;
    }
  }
  // track 4
  else if ((trackPlaying == 1) && (randomTrack == 4)) {
    // get track duration
    trackDuration = 189387;
    if (currentMillis - trackOnTime >= trackDuration) {
      sfx.stop();
      trackPlaying = 0;
    }
  }
  // track 5
  else if ((trackPlaying == 1) && (randomTrack == 5)) {
    // get track duration
    trackDuration = 222040;
    if (currentMillis - trackOnTime >= trackDuration) {
      sfx.stop();
      trackPlaying = 0;
    }
  }
  // track 6
  else if ((trackPlaying == 1) && (randomTrack == 6)) {
    // get track duration
    trackDuration = 175151;
    if (currentMillis - trackOnTime >= trackDuration) {
      sfx.stop();
      trackPlaying = 0;
    }
  }
  // track 7
  else if ((trackPlaying == 1) && (randomTrack == 7)) {
    // get track duration
    trackDuration = 172224;
    if (currentMillis - trackOnTime >= trackDuration) {
      sfx.stop();
      trackPlaying = 0;
    }
  }
  // no track playing
  else {
    // pick the random track
    randomTrack = random(0, 8);
    while (randomTrack == previousTrack) {
      randomTrack = random(0, 8);
    }
    previousTrack = randomTrack;
    // start playing the track
    sfx.playTrack(randomTrack);
    // get track start time
    trackOnTime = millis();
    // toggle trackPlaying to on
    trackPlaying = 1;
  }
}
