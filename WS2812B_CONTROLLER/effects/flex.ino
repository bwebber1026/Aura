#include <Arduino.h>

void flex() {

  MILLISECONDS  = 0;
  lowPass_audio = 0.07;
  //filter_min    = 150;

  //  left_current_brightness = 0;
  //  right_current_brightness = 0;
  //  left_next_brightness = 0;
  //  right_next_brightness = 0;
  //  current_hue = 0;
  //  next_hue = 0;

  spectrumWidth = 31;
  fhue = 0;

  left_pos    = HALF_POS;
  left_point  = HALF_POS;
  right_pos   = HALF_POS;
  right_point = HALF_POS;

  for (int band = 0; band < 7; band++) {

    left_point   -= mapped_left[band];
    right_point  +=  mapped_right[band];

    if (band == 0) {
      current_hue = fhue;
      next_hue = fhue + spectrumWidth;
      left_current_brightness  = map(left[0], 0, 255, 0, 200);
      right_current_brightness = map(right[0], 0, 255, 0, 200);
      left_next_brightness     = map(left[band + 1], 0, 255, 0, 200);
      right_next_brightness    = map(right[band + 1], 0, 255, 0, 200);
    }

    else if (band < 6) {
      current_hue = next_hue;
      next_hue = fhue + ((band + 1) * spectrumWidth);
      left_current_brightness  = left_next_brightness;
      right_current_brightness = right_next_brightness;
      left_next_brightness     = map(left[band + 1], 0, 255, 0, 200);
      right_next_brightness    = map(right[band + 1], 0, 255, 0, 200);
    }

    else if (band == 6) {
      current_hue = next_hue;
      next_hue = fhue + (7 * spectrumWidth);
      left_current_brightness  = left_next_brightness;
      right_current_brightness = right_next_brightness;
      left_next_brightness     = left_current_brightness;
      right_next_brightness    = right_current_brightness;

      left_point = 0;
      right_point = NUM_LEDS - 1;
    }

    fill_gradient(leds, left_pos,  CHSV(current_hue, 255, left_current_brightness),  left_point,  CHSV(next_hue, 255, left_next_brightness),  SHORTEST_HUES);
    fill_gradient(leds, right_pos, CHSV(current_hue, 255, right_current_brightness), right_point, CHSV(next_hue, 255, right_next_brightness), SHORTEST_HUES);

    left_pos  = left_point;
    right_pos = right_point;

  }

  //FastLED.show();

  EVERY_N_MILLISECONDS(6) {
    //blur1d(leds, NUM_LEDS, 1);
    fadeToBlackBy(leds, NUM_LEDS, 1);
  }

  //fill_solid(leds, NUM_LEDS, CRGB::Black);

}
