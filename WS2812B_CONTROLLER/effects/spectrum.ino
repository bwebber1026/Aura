#include <Arduino.h>

void spectrum() {

  //fadeToBlackBy(leds,NUM_LEDS,65);
  pos = 0;
  point = 4;

  filter_min = 150;
  lowPass_audio = 0.15;

  spectrumWidth = 36;
  hue = 216;

  //  if (left[0] > 140) hue -= left[0] * 0.01;
  //  hue = 0;
  //  if (hue > 255) hue = 0;

  // fill pre-segments
  current_brightness = left[6] * 0.25;
  current_hue = hue;
  fill_gradient(leds, pos, CHSV(current_hue, 255, 0), point, CHSV(current_hue, 255, current_brightness), SHORTEST_HUES);
  pos = point;

  for (int band = 6; band > -1; band--) {
    k = (band - 1) % 7; // debug...
    point += segmentEnd[band];
    current_brightness = left[band] * 0.25;
    current_hue = hue + (band * spectrumWidth); // COLOR FROM PALETTE

    if (band > 0) {
      next_brightness = (left[k] * 0.25); // CAN JUST LOWER THIS TO CREATE EDGES INSTEAD OF /*next_brightness * 0.6*/
      next_hue = hue + ((band - 1) * spectrumWidth);
      fill_gradient(leds, pos, CHSV(current_hue, 255, current_brightness), point, CHSV(next_hue, 255, next_brightness), SHORTEST_HUES);

    } else {
      next_brightness = 0; // help this out to make it go further to the egde! more color!
      next_hue = hue;
      fill_gradient(leds, pos, CHSV(current_hue, 255, current_brightness), point, CHSV(next_hue, 255, next_brightness), SHORTEST_HUES);
    }
    pos = point;
  }

  fill_gradient(leds, pos, CHSV(next_hue, 255, next_brightness), NUM_LEDS - 2, CHSV(next_hue, 255, 0), SHORTEST_HUES);
  //FastLED.show();
}
