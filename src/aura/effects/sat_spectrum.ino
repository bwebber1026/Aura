#include <Arduino.h>

void sat_spectrum() {

  pos = 0;
  point = 0;

  MILLISECONDS  = 10;
  lowPass_audio = 0.1;
  //filter_min    = 0;
  spectrumWidth = 34;
  hue = 0;

  //  EVERY_N_MILLISECONDS(20) {
  //    if (mono[0] > 50) hue--;;
  //  }
  //if(mono[0] > 80) hue++;

  for (int band = 0; band < 7; band++) {

    point += segmentEnd[band];
    current_brightness = map(mono[band], 0, 255, 255, 0);
    current_hue = hue + (band * spectrumWidth); // COLOR FROM PALETTE

    if (band < 6) {
      next_brightness = map(mono[band + 1], 0, 255, 255, 0); // CAN JUST LOWER THIS TO CREATE EDGES INSTEAD OF /*next_brightness * 0.6*/
      next_hue = hue + ((band + 1) * spectrumWidth);
      fill_gradient(leds, pos, CHSV(hue, current_brightness, 255), point, CHSV(hue, next_brightness, 255), SHORTEST_HUES);

    } else {
      next_brightness = current_brightness; // help this out to make it go further to the egde! more color!
      next_hue = current_hue;
      fill_gradient(leds, pos, CHSV(hue, current_brightness, 255), NUM_LEDS - 1, CHSV(hue, next_brightness, 255), SHORTEST_HUES);
    }
    pos = point;
  }

  //EVERY_N_MILLISECONDS(5) {
  //fadeToBlackBy(leds, NUM_LEDS, 1);
  //blur1d(leds, NUM_LEDS, 60);
  //nscale8(leds,NUM_LEDS,70);

  //}
  //FastLED.show();
}
