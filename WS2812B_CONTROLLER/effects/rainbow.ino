#include <Arduino.h>

void rainbow() {
  EVERY_N_MILLISECONDS(20) {
    hue--;
    if (hue > 255) hue = 0;
  }
  fill_rainbow(leds, NUM_LEDS, hue, 1);
  addGlitter(80);

}
