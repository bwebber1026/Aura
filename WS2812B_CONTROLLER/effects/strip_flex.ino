#include <Arduino.h>

void strip_flex() {

  pos = 0;
  point = 0;

  MILLISECONDS = 10;
  lowPass_audio = 0.08;
  spectrumWidth = 32;

  //fhue += mono[0] * .05;
  //  EVERY_N_MILLISECONDS(200){
  //    fhue++;
  //  }

  for (int band = 0; band < 7; band++) {

    current_brightness = map(mono[band], 50, 255, 50, 200);

    if (band < 6) {
      next_brightness  = map(mono[band + 1], 50, 255, 50, 200);
    } else {
      next_brightness  = current_brightness;
    }

    current_hue = fhue + (band * spectrumWidth);
    next_hue = fhue + ((band + 1) * spectrumWidth);

    point +=  full_flex[band];

    fill_gradient(leds, pos, CHSV(current_hue, 255, current_brightness), point, CHSV(next_hue, 255, next_brightness), SHORTEST_HUES);

    pos = point;
  }

  fadeToBlackBy(leds, NUM_LEDS, 1);
  //blur1d(leds, NUM_LEDS, 70);
  //FastLED.show();
}
