#include <Arduino.h>

//void flex() {
//
//  lowPass_audio = 0.15; // .10
//  //  filter_min  = 70; // STILL 93*????  //175
//
//  left_pos    = HALF_POS;
//  left_point  = HALF_POS;
//  right_pos   = HALF_POS;
//  right_point = HALF_POS;
//
//  k = 0;
//
//  spectrumWidth = 35;
//  hue = 0;
//
//  for (int band = 0; band < 13; band++) {
//
//    k = (band + 1) % 7;
//
//    left_point   -= mapped_left[band]; //MOVE OUT TO THE RIGHT
//    right_point  +=  mapped_right[band];  // TO LEFT..
//
//    current_hue = hue + band * spectrumWidth; // COLOR FROM PALETTE
//    left_current_brightness  = left[band] * 0.25;
//    right_current_brightness = right[band] * 0.25;
//
////    if (band < 6) {
////      next_hue = hue + ((band + 1) * spectrumWidth);
////      left_next_brightness  = (left[k]  * 0.25); // CAN JUST LOWER THIS TO CREATE EDGES INSTEAD OF /*next_brightness * 0.6*/
////      right_next_brightness = (right[k] * 0.25); // CAN JUST LOWER THIS TO CREATE EDGES INSTEAD OF /*next_brightness * 0.6*/
////    } else {
////      //left_next_hue = left_current_brightness;
////      //right_next_hue = right_current_brightness; // just to add white tail? 12-23
////      next_hue = hue + band * spectrumWidth;
////      left_next_brightness  = 0; // help this out to make it go further to the egde! more color!
////      right_next_brightness = 0; // help this out to make it go further to the egde! more color!
////    }
//
////    if (band < 6) {
////      current_brightness = left[band] * 0.25;
////      next_brightness = left[band + 1]  * 0.25;
////    } else if (band == 6) {
////      current_brightness = left[band] * 0.25;
////      next_brightness = right[band - 7] * 0.25;
////    } else {
////      current_brightness = right[band - 7] * 0.25;
////      next_brightness = right[band - 8] * 0.25;
////    }
//
//
//    //    left_current_sat  = 100 + (left_current_brightness * 0.60);
//    //    right_current_sat = 100 + (right_current_brightness * 0.60);
//    //    left_next_sat  = 100 + (left_next_brightness * 0.60);
//    //    right_next_sat = 100 + (right_next_brightness * 0.60);
//
//    //    left_current_sat  = left_current_brightness;
//    //    right_current_sat = right_current_brightness;
//    //    left_next_sat     = left_next_brightness;
//    //    right_next_sat    = right_next_brightness;
//
//    left_current_sat  = 255;
//    right_current_sat = 255;
//    left_next_sat     = 255;
//    right_next_sat    = 255;
//
//    fill_gradient(leds, left_pos, CHSV(current_hue, left_current_sat, left_current_brightness), left_point, CHSV(next_hue, left_next_sat, left_next_brightness),  SHORTEST_HUES);
//    fill_gradient(leds, right_pos, CHSV(current_hue, right_current_sat, right_current_brightness), right_point, CHSV(next_hue, right_next_sat, right_next_brightness), SHORTEST_HUES);
//
//    left_pos  = left_point;
//    right_pos = right_point;
//  }
//
//  //blur1d(leds, NUM_LEDS, 140);
//  //FastLED.show();
//}
