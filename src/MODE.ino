#include <Arduino.h>

int mode = 4;
//CRGB leds2[NUM_LEDS];
//CRGB leds3[NUM_LEDS];

void MODE() {

  //  EVERY_N_SECONDS(5) {
  //    mode++;
  //    if (mode > 4) {
  //      mode = 0;
  //    }
  //  }

  switch (mode) {
    case 0:
      flex_mono();
      break;
    case 1:
      radiate();
      break;
    case 2:
      radiate();
      break;
    case 3:
      audio_data();
      break;
    case 4:
      spectrum142();
      break;
    case 5:
      rainbow();
      break;
    case 6:
      flex();
      break;
    case 7:
      ambient();
      break;
    case 8:
      Fire2012();
      break;
    case 9:
      audio_data_stereo();
      break;
    case 10:
      spectrumcolor();
      break;
    case 11:
      sat_spectrum();
      break;
    case 12:
      strip_flex();
      break;
    case 13:
      print_audio();
      break;
    case 14:
      juggle();
      break;
    case 15:
      sinelon();
      break;
    case 16:
      confetti();
      break;
    case 17:
      splatter();
      break;
    case 18:
      bpm();
      break;
    default:
      flex_mono(); //this can be whatever default mode you want
      break;
  }

  // set the blend ratio for the video cross fade
  // (set ratio to 127 for a constant 50% / 50% blend)
  //uint8_t ratio = beatsin8(5);

  // mix the 2 arrays together
  //for (int i = 0; i < NUM_LEDS; i++) {
  //  leds[i] = blend( leds2[i], leds3[i], ratio );
  //}
  FastLED.show();
  FastLED.delay(1000 / FRAMES_PER_SECOND);

  /*
    FLEXFLEX();
    ambient();
    audio_spectrum();
    stereo_vu();
    flexflexstereo();
    flex_stereo();
    Fire2012(); // run simulation frame
  */

}
