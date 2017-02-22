#include <Arduino.h>

void audio_data() {

  lowPass_audio = 0.1;
  MILLISECONDS = 10;
  filter_min  = 100;
  spectrumWidth = 4;

  int pos = 0;
  int point = 0;

  for (int band = 0; band < 7; band++) {
    point += 20;
    if (band == 6) point = NUM_LEDS - 1;
    hue = band * spectrumWidth;

    BRIGHTNESS = mono[band];

    for (int i = pos; i < point; i++) {
      leds[i] = CHSV(hue, 255, BRIGHTNESS);
    }
    pos = point;
  }
  //FastLED.show();
}

int left_hue;
int right_hue;
int left_brightness;
int right_brightness;

void audio_data_stereo() {

  lowPass_audio = 0.12;
  MILLISECONDS = 10;
  //filter_min  = 100;
  spectrumWidth = 33;

  //  EVERY_N_MILLISECONDS(100) {
  //    hue++;
  //  }

  int pos = 0;
  int point = 0;

  for (int band = 0; band < 7; band++) {
    point += 10;

    left_brightness  = map(left[band], 0, 255, 0, 150);
    right_brightness = map(right[band], 0, 255, 0, 150);

    hue = band * spectrumWidth;
    //left_hue = hue + (left_brightness * 0.25);
    //right_hue = hue + (right_brightness * 0.25);

    if (band == 0) {
      left_brightness = map(mono[0], 0, 255, 0, 150);
      right_brightness = left_brightness;
      point = 12;
    }


    for (int i = HALF_POS + pos; i < HALF_POS + point; i++) {
      leds[i] = CHSV(hue, 255, left_brightness);
    }
    for (int i = HALF_POS - pos; i > (HALF_POS - point); i--) {
      leds[i] = CHSV(hue, 255, right_brightness);
    }
    pos = point;
  }
  blur1d(leds, NUM_LEDS, 10);
  //FastLED.show();
}

//void audio_data() {
//
//  hue = 0;
//  int INDEX = 0;
//
//  changePalette();
//
//  for (int i = 0; i < NUM_LEDS; i++) {                                    // Just ONE loop to fill up the LED array as all of the pixels change.
//    uint8_t index = inoise8(i * scale, dist + scale, z) % 255;            // Get a value from the noise function. I'm using both x and y axis.
//    hues[i] = ColorFromPalette(gCurrentPalette, index, 255, LINEARBLEND); // With that value, look up the 8 bit colour palette value and assign it to the current LED.
//  }
//  //dist += beatsin8(10, 1, 4);                                           // Moving along the distance (that random number we started out with). Vary it a bit with a sine wave
//
//
//  for (int band = 0; band < 7; band++) {
//    //hue = 252 - (band * 36);
//    //hue = 215;
//    for (int i = INDEX; i < (INDEX + segmentSize); i++) {
//      leds[i] = CHSV(hues[i], 255, mono[band] * 0.25);
//    }
//    INDEX += segmentSize;
//  }
//  //FastLED.show();
//}
