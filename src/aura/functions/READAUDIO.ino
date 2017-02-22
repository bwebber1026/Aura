#include <Arduino.h>

void READ_AUDIO() {

  prev_left  = left_volume;
  prev_right = right_volume;

  prev_left_amp  = half_MAPPED_LEFT_AMP;
  prev_right_amp = half_MAPPED_RIGHT_AMP;

  left_volume  = 0.0;
  right_volume = 0.0;
  mono_volume  = 0;
  left_factor  = 0.0;
  right_factor = 0.0;
  mono_factor  = 0;

  digitalWrite(MSGEQ7_RESET_PIN, HIGH);
  digitalWrite(MSGEQ7_RESET_PIN, LOW);
  delayMicroseconds(1);

  for (int band = 0; band < 7; band++)
  {

    filter_min = FILTER_MIN[band];
    digitalWrite(MSGEQ7_STROBE_PIN, LOW);
    delayMicroseconds(36);

    prev_value  = left[band];
    left_value  = analogRead(AUDIO_LEFT_PIN);
    //left_value  -= (left_value * EQ[band]);
    left_value  = constrain(left_value, filter_min, filter_max);
    left_value  = map(left_value, filter_min, filter_max, 0, 255);
    left[band]  = prev_value + (left_value - prev_value) * lowPass_audio;
    left_volume += left[band];


    prev_value   = right[band];
    right_value  = analogRead(AUDIO_RIGHT_PIN);
    //right_value  -= (right_value * EQ[band]);
    right_value  = constrain(right_value, filter_min, filter_max);
    right_value  = map(right_value, filter_min, filter_max, 0, 255);
    right[band]  = prev_value + (right_value - prev_value) * lowPass_audio;
    right_volume += right[band];

    digitalWrite(MSGEQ7_STROBE_PIN, HIGH);
    delayMicroseconds(1);

    mono[band]   = (left[band] + right[band]) * 0.5;
    mono_volume += mono[band];

    //IF DEF is (this effect) then do these extra/specfic tasks *stereo_vu*
  }

  //mono_volume  /= 7;
  //left_volume  /= 7;
  //right_volume /= 7;
//  new_left = (left_volume  / 7);
//  new_left = prev_left + (new_left - prev_left) * 0.005;
//  new_right = (right_volume / 7);
//  new_right = prev_right + (new_right - prev_right) * 0.005;
//
//  left_filter_max  = new_left;
//  right_filter_max = new_right;


  left_factor   = float(HALF_POS) / left_volume;
  right_factor  = float(HALF_POS) / right_volume;
  mono_factor   = float(HALF_POS) / mono_volume;
  //if(mono_factor < 0.01) mono_factor = 0;
  full_factor   = float(NUM_LEDS) / mono_volume;

  for (int band = 0; band < 7; band++)
  {

    full_flex[band] = mono[band] * full_factor;

    mapped[band]    = mono[band] * mono_factor;

    //    if (half_MAPPED_AMP < 2) {
    //      half_MAPPED_AMP -= 2;
    //    }
    //    mapped[band] = half_MAPPED_AMP;

    half_MAPPED_LEFT_AMP = floor(left[band]  * left_factor);
    //    if (half_MAPPED_LEFT_AMP < 3) {
    //      half_MAPPED_LEFT_AMP -= 3;
    //    }
    mapped_left[band]    = half_MAPPED_LEFT_AMP;

    half_MAPPED_RIGHT_AMP = floor(right[band] * right_factor);
    //    if (half_MAPPED_RIGHT_AMP < 2) {
    //      half_MAPPED_RIGHT_AMP -= 2;
    //    }
    mapped_right[band]    = half_MAPPED_RIGHT_AMP;


    //full_mapped[band]     = left[6 - band]  * left_factor;
    //full_mapped[band + 7] = right[band] * right_factor;

    // }

  }
}
