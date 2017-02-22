#include <Arduino.h>

void spectrumcolor() {

  pos = 0;
  point = 0;

  MILLISECONDS  = 0;
  lowPass_audio = 0.12;
  //filter_min    = 0;
  spectrumWidth = 0;
  hue = 200;

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
    current_brightness = map(mono[band], 50, 255, 50, 255);
    current_hue = hue + ((band * spectrumWidth) /*+ (mono[band] * .2)*/); // COLOR FROM PALETTE

    if (band < 6) {
      next_brightness = map(mono[band + 1], 50, 255, 50, 255); // CAN JUST LOWER THIS TO CREATE EDGES INSTEAD OF /*next_brightness * 0.6*/
      next_hue = hue + (((band + 1) * spectrumWidth) /*+ (mono[band] * .2)*/);
      fill_gradient(leds, pos, CHSV(current_hue, 255, current_brightness), point, CHSV(next_hue, 255, next_brightness), SHORTEST_HUES);

    } else {
      next_brightness = current_brightness; // help this out to make it go further to the egde! more color!
      //next_hue = hue;
      fill_gradient(leds, pos, CHSV(current_hue, 255, current_brightness), NUM_LEDS - 1, CHSV(next_hue, 255, next_brightness), SHORTEST_HUES);
    }
    pos = point;
  }

  //blur1d(leds, NUM_LEDS, 30);
  //nscale8(leds,NUM_LEDS,50);
  //FastLED.show();
}
