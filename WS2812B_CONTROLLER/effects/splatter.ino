#include <Arduino.h>

void splatter() {

  changePalette();

  MILLISECONDS  = 10;
  lowPass_audio = 0.15;

  READ_AUDIO();

  //EVERY_N_MILLISECONDS(10) {
  fadeToBlackBy( leds, NUM_LEDS, 1);
  //}

  blur1d(leds, NUM_LEDS, 150);

  for (int band = 0; band < 7; band++) {

    hue = band * 36;
//    hue = ColorFromPalette(gCurrentPalette, index, 255, LINEARBLEND);

    EVERY_N_MILLISECONDS(60) {
      //if (mono[band] > 10) {
      pos = random16(NUM_LEDS - 1);
      left_pos  = pos - random(0, 5);
      right_pos = pos + random(0, 5);
      if (left_pos < 0) {
        left_pos = 0;
      }
      if (right_pos > NUM_LEDS - 1) {
        right_pos = NUM_LEDS - 1;
      }
      //}
    }

    for (int i = left_pos; i < right_pos; i++) {
      leds[i] += CHSV( hue, 255, mono[band]);
    }


  }
}

void addGlitter( fract8 chanceOfGlitter)
{
  if ( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CRGB::White;
  }
}
