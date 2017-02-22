#include <Arduino.h>

void juggle() {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds, NUM_LEDS, 20);
  byte dothue = 0;
  for ( int i = 0; i < 8; i++) {
    leds[beatsin16(i + 7, 0, NUM_LEDS)] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
}

void sinelon()
{

  EVERY_N_MILLISECONDS(50) {
    hue++;
  }
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 1);
  int pos = beatsin16(13, 0, NUM_LEDS - 1);
  leds[pos] += CHSV( hue, 255, 192);
}

void confetti()
{
  changePalette();
  EVERY_N_MILLISECONDS(50) {
    blur1d(leds, NUM_LEDS, 50);
  }

  EVERY_N_MILLISECONDS(65) {
    fadeToBlackBy(leds, NUM_LEDS, 1);
  }

  //MILLISECONDS = beatsin8(30,800,150);

  EVERY_N_MILLISECONDS(250) {
    //fhue = random8(30);
    pos = random16(NUM_LEDS - 1);
    //hue += 3;
    INDEX += 15;


    left_pos  = pos - random(1, 9);
    right_pos = pos + random(1, 9);
    if (left_pos < 0) {
      left_pos = 0;
    }
    if (right_pos > NUM_LEDS - 1) {
      right_pos = NUM_LEDS - 1;
    }

    for (int i = left_pos; i < right_pos; i++) {
      //leds[i] += CHSV( hue /*+ fhue*/, 255, 255);
      leds[i] += ColorFromPalette(gCurrentPalette, INDEX, 130, LINEARBLEND);
    }
  }
}

void bpm()
{

  EVERY_N_MILLISECONDS(60) {
    hue++;
  }
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for ( int i = 0; i < NUM_LEDS; i++) { //9948
    leds[i] = ColorFromPalette(palette, hue + (i * 2), beat - hue + (i * 10));
  }
}
