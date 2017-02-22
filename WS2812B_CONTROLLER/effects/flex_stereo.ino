#include <Arduino.h>

void flex_stereo() {

  lowPass_audio = 0.1;
  MILLISECONDS = 10;
  filter_min  = 150;
  spectrumWidth = 28;

  pos = 0;
  point = pos;

  spectrumWidth = 36;

  for (int band = 0; band < 14; band++) {

    current_hue = HUEZ[band];
    next_hue    = HUEZ[band + 1];

    point += full_mapped[band];

    if (band < 6) {
      current_brightness = right[6 - band] * 0.25;
      next_brightness = right[5 - band]  * 0.25;
    } else if (band == 6) {
      current_brightness = right[0] * 0.25;
      next_brightness = left[0] * 0.25;
    } else {
      current_brightness = left[band - 6] * 0.25;
      next_brightness = left[band - 5] * 0.25;
    }

    fill_gradient(leds, pos, CHSV(current_hue, 255, current_brightness), point, CHSV(next_hue, 255, next_brightness),  SHORTEST_HUES);


    pos = point;

  }

  blur1d(leds, NUM_LEDS, 100);

  //FastLED.show();
}
