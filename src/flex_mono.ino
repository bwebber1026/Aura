#include <Arduino.h>

void flex_mono() {

  changePalette();

  left_pos    = HALF_POS;
  left_point  = HALF_POS;
  right_pos   = HALF_POS;
  right_point = HALF_POS;

  MILLISECONDS = 10;
  lowPass_audio = 0.10;
  spectrumWidth = 35;

  //fhue += mono[0] * .05;
  //  EVERY_N_MILLISECONDS(200){
  //    fhue++;
  //  }

  for (int band = 0; band < 7; band++) {

    left_current_brightness = map(left[band], 30, 255, 50, 255);
    right_current_brightness = left_current_brightness;

    if (band < 6) {
      left_next_brightness  = map(left[band + 1], 30, 255, 50, 255);
      right_next_brightness = left_next_brightness;
    } else {
      left_next_brightness  = 0;
      right_next_brightness = 0;
    }

    current_hue = fhue + (band * spectrumWidth);
    next_hue = fhue + ((band + 1) * spectrumWidth);

    left_point -=  mapped_left[band];
    right_point += mapped_left[band];


    //if (band == 6) (left_point = 0) && (right_point = NUM_LEDS - 1) && (next_hue = band * 35) /*&& (left_next_brightness = 0) && (right_next_brightness = 0)*/;

    fill_gradient(leds, left_pos, CHSV(current_hue, 255, left_current_brightness), left_point, CHSV(next_hue, 255, right_next_brightness), SHORTEST_HUES);
    fill_gradient(leds, right_pos, CHSV(current_hue, 255, right_current_brightness), right_point, CHSV(next_hue, 255, right_next_brightness), SHORTEST_HUES);

    //fill_gradient(leds, left_pos, ColorFromPalette(gCurrentPalette, current_hue, left_current_brightness, LINEARBLEND), left_point, ColorFromPalette(gCurrentPalette, next_hue, right_next_brightness, LINEARBLEND), SHORTEST_HUES);
    //fill_gradient(leds, right_pos, ColorFromPalette(gCurrentPalette, current_hue, right_current_brightness, LINEARBLEND), right_point, ColorFromPalette(gCurrentPalette, next_hue, right_next_brightness, LINEARBLEND), SHORTEST_HUES);

    //current_hue += 12;
    //next_hue += 12;

    left_pos  = left_point;
    right_pos = right_point;
  }

  //fadeToBlackBy(leds,NUM_LEDS,1);
  blur1d(leds, NUM_LEDS, 130);
  //nblend(leds, NUM_LEDS, 130);
  //FastLED.show();
}
