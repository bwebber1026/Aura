#include <Arduino.h>

void audio_spectrum() {

  changePalette();

  pos = 0;
  point = 0;
  k = 0;

  for (int band = 0; band < 7; band++) {
    k = (band + 1) % 7; // debug...
    point += segmentEnd[band];
    //current_hue = band * 36; // COLOR FROM PALETTE
    current_brightness = mono[band] * 0.25;
    current_hue = ColorFromPalette(gCurrentPalette, colorIndex + band, current_brightness, LINEARBLEND);
    if (band < 6) {
      next_brightness = (mono[k] * 0.25); // CAN JUST LOWER THIS TO CREATE EDGES INSTEAD OF /*next_brightness * 0.6*/
      next_hue = ColorFromPalette(gCurrentPalette, colorIndex, next_brightness, LINEARBLEND);

      //next_hue = (band + 1) * 35;
    } else {
      next_brightness = mono[band] * 0.25; // help this out to make it go further to the egde! more color!
      next_hue = ColorFromPalette(gCurrentPalette, colorIndex, next_brightness, LINEARBLEND);
      //next_hue = band * 35;
    }

    fill_gradient(leds, pos, CHSV(current_hue, 255, current_brightness), point, CHSV(next_hue, 255, next_brightness), FORWARD_HUES);
    pos = point;
  }

//  for (int i = 0; i < NUM_LEDS; i++) {
//    leds[i] = hues[i];
//  }
  //FastLED.show();
}
