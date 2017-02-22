#include <Arduino.h>

void flexflexstereo() {

  left_pos    = HALF_POS;
  left_point  = HALF_POS;
  right_pos   = HALF_POS;
  right_point = HALF_POS;

  lowPass_audio = 0.1;
  filter_min  = 130;
  spectrumWidth = 30;

  for (int band = 0; band < 7; band++) {

    left_current_brightness = map(left[band], 0, 255, 100, 255);
    right_current_brightness = map(right[band], 0, 255, 100, 255);

    if (band < 6) {
      left_next_brightness = map(left[band + 1], 0, 255, 100, 255);
      right_next_brightness = map(right[band + 1], 0, 255, 100, 255);

    } else {
      left_next_brightness = left_current_brightness;
      right_next_brightness = right_current_brightness;
    }

    current_hue = band * spectrumWidth;
    next_hue = (band + 1) * spectrumWidth;

    left_point -=  mapped_left[band];
    right_point += mapped_right[band];

    if (band == 6) (left_point = 0) && (right_point = NUM_LEDS - 1) && (next_hue = band * spectrumWidth) /*&& (left_next_brightness = 0) && (right_next_brightness = 0)*/;

    fill_gradient(leds, left_pos, CHSV(current_hue, 255, left_current_brightness), left_point, CHSV(next_hue, 255, left_next_brightness), SHORTEST_HUES);
    fill_gradient(leds, right_pos, CHSV(current_hue, 255, right_current_brightness), right_point, CHSV(next_hue, 255, right_next_brightness), SHORTEST_HUES);

    left_pos  = left_point;
    right_pos = right_point;
  }

  blur1d(leds, NUM_LEDS, 2);
  FastLED.show();
}
