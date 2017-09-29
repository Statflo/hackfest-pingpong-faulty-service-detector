#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "Music.cpp"

int sigState = 0;

int globalSensorA0Value = 0;
int globalSensorA1Value = 0;
int globalSensorA2Value = 0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, ledID, NEO_GRB + NEO_KHZ800);
Music music             = Music();

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
    if(WheelPos < 85) {
        return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
    } else if(WheelPos < 170) {
        WheelPos -= 85;
        return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
    } else {
        WheelPos -= 170;
        return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
    }
}

void rainbowCycle(uint8_t wait) {
    uint16_t i, j;

    strip.setBrightness(100);

    for(j=0; j<256*1; j++) { // 5 cycles of all colors on wheel
        for(i=0; i< strip.numPixels(); i++) {
            strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
        }
        strip.show();
        delay(wait);
    }
}

void reset()
{
    strip.setBrightness(0);
    strip.show();
    noTone(speakerID);
    sigState = 0;
}

void setup()
{
    Serial.begin(9600);
    pinMode(sensorID1, INPUT);
    pinMode(sensorID2, INPUT);
    pinMode(sensorID3, INPUT);
    pinMode(speakerID, OUTPUT);
    strip.begin();
    strip.show();
    reset();
}

void net()
{
    rainbowCycle(1);
    music.playMusic();
}

int getSensorValue()
{
  int sensorA0Value = analogRead("A0");
  Serial.println("sensor a0 value:");
  Serial.println(sensorA0Value);

  int sensorA1Value = analogRead("A1");
  Serial.println("sensor a1 value:");
  Serial.println(sensorA1Value);

  int sensorA2Value = analogRead("A2");
  Serial.println("sensor a2 value:");
  Serial.println(sensorA2Value);

  int A0ValueDifferential = abs(sensorA0Value - globalSensorA0Value);
  globalSensorA0Value = sensorA0Value;

  int A1ValueDifferential = abs(sensorA1Value - globalSensorA1Value);
  globalSensorA1Value = sensorA1Value;

  int A2ValueDifferential = abs(sensorA2Value - globalSensorA2Value);
  globalSensorA2Value = sensorA2Value;

  if(A0ValueDifferential >= 300 && A1ValueDifferential >= 300 && A2ValueDifferential >= 300)
    return HIGH;
  else
    return LOW;

}

void loop()
{
    sigState = getSensorValue();

    Serial.println("sigState");
    Serial.println(sigState);
    Serial.println("===================");
    delay(100);

    if (sigState == HIGH)
    {
        net();
        reset();
    }
}
