#include <Arduino.h>

void stereo_vu() {
  fadeToBlackBy(leds, NUM_LEDS, 50);

  //fill_solid(leds, NUM_LEDS, CHSV(hue + 70, 255, 255));
  hue += mono[0] * 0.01;
  if(hue > 255) hue = 0;

  // from center to left
  for (int i = HALF_POS; i > map(left_volume, 0, filter_max, HALF_POS, 0); i--) {
    leds[i] = CHSV(hue + 220, 255, 255);
    //leds[i] = ColorFromPalette(gCurrentPalette, hue, 255);
  }
  // move to the right
  for (int i = HALF_POS; i < map(right_volume, 0, filter_max, HALF_POS, NUM_LEDS - 1); i++) {
    leds[i] = CHSV(hue +  220, 255, 255);
    //leds[i] = ColorFromPalette(gCurrentPalette, hue, 255);
  }

  blur1d(leds, NUM_LEDS, 60);
  //FastLED.show();

}
