#include <Arduino.h>

void spectrum142() {

  pos = 0;
  point = 0;

  MILLISECONDS  = 0;
  lowPass_audio = 0.18;
  //filter_min    = 0;
  spectrumWidth = 34;
  hue = 0;

  //  EVERY_N_MILLISECONDS(20) {
  //    if (mono[0] > 50) hue--;;
  //  }
  //if(mono[0] > 80) hue++;

  // fill pre-segments
  //current_brightness = left[6] * 0.25;
  //current_hue = hue;
  //fill_gradient(leds, pos, CHSV(current_hue, 255, 0), point, CHSV(current_hue, 255, current_brightness), SHORTEST_HUES);
  //pos = point;

  for (int band = 0; band < 7; band++) {
    //k = (band + 1) % 7; // debug...
    point += segmentEnd[band];
    current_brightness = map(mono[band], 10, 255, 10, 255);
    current_hue = hue + (band * spectrumWidth); // COLOR FROM PALETTE

    if (band < 6) {
      next_brightness = map(mono[band + 1], 10, 255, 10, 255); // CAN JUST LOWER THIS TO CREATE EDGES INSTEAD OF /*next_brightness * 0.6*/
      next_hue = hue + ((band + 1) * spectrumWidth);
      fill_gradient(leds, pos, CHSV(current_hue, 255, current_brightness), point, CHSV(next_hue, 255, next_brightness), SHORTEST_HUES);

    } else {
      next_brightness = current_brightness; // help this out to make it go further to the egde! more color!
      next_hue = current_hue;
      fill_gradient(leds, pos, CHSV(current_hue, 255, current_brightness), NUM_LEDS - 1, CHSV(next_hue, 255, next_brightness), SHORTEST_HUES);
    }
    pos = point;
  }

  //EVERY_N_MILLISECONDS(5) {
  //fadeToBlackBy(leds, NUM_LEDS, 1);
  blur1d(leds, NUM_LEDS, 160);
  //nscale8(leds,NUM_LEDS,70);

  //}
  //FastLED.show();
}
