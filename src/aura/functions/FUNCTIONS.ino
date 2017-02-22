#include <Arduino.h>

// #ifdef DEBUG
void printAudio() {
  for (int band = 0; band < 7; band++)
  {
    Serial.print(int(mono[band] * .25));
    Serial.print("\t");
  }
  Serial.println();
}
// #endif

void showAnalogRGB( const CRGB& rgb)
{
  analogWrite(REDPIN,   255 - rgb.r );
  analogWrite(GREENPIN, 255 - rgb.g );
  analogWrite(BLUEPIN,  255 - rgb.b );
}

/*
void mod_test() {
  Serial.println("start");
  delay(500);
  for (int band = 0; band < 13; band++) {
    k = (band + 6) % 13;
    Serial.println(k);
    delay(500);
  }
}
*/
