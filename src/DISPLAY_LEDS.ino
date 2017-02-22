#include <Arduino.h>

void DISPLAY_LEDS() {

  displayRGB();

}

void displayRGB() {
  //showAnalogRGB(CHSV(hue, 255, value));
  //  switch (encoderStatus) {
  //    case 1:
  showAnalogRGB( CRGB(left[0] * 0.25, left[2] * 0.25, left[5] * 0.25));
  //      break;
  //  }
}
