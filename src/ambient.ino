#include <Arduino.h>

void ambient() {
  //READ_AUDIO();
  changePalette();
  scale = 2;

  for (int i = 0; i < NUM_LEDS; i++) {                                     // Just ONE loop to fill up the LED array as all of the pixels change.
    uint8_t index = inoise8(i * scale, dist + scale, z) % 255;             // Get a value from the noise function. I'm using both x and y axis.
    leds[i] = ColorFromPalette(gCurrentPalette, index, 255, LINEARBLEND);  // With that value, look up the 8 bit colour palette value and assign it to the current LED.
  }
  //dist += beatsin8(10, 1, 4);                                             // Moving along the distance (that random number we started out with). Vary it a bit with a sine wave
  //dist += mono[4] * .03;
  z += .5 + (mono[0] * .03);

  //FastLED.show();
}

void audio_ambient() {
  changePalette();
  scale = 13;

  for (int i = 0; i < NUM_LEDS; i++) {                                     // Just ONE loop to fill up the LED array as all of the pixels change.
    uint16_t index = inoise8(i * scale, dist + scale, z) % 255;             // Get a value from the noise function. I'm using both x and y axis.
    leds[i] = ColorFromPalette(gCurrentPalette, index, 255, LINEARBLEND);  // With that value, look up the 8 bit colour palette value and assign it to the current LED.
  }
  //dist += beatsin8(30, 1, 2);                                            // Moving along the distance (that random number we started out with). Vary it a bit with a sine wave
  dist += mono[0] * .03;

  //EVERY_N_MILLISECONDS(8) {
  //z++;
  //}
  blur1d(leds, NUM_LEDS, 60);
  //FastLED.show();
}
