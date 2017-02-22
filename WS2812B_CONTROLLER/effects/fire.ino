#include <Arduino.h>

void Fire2012()
{
  // Array of temperature readings at each simulation cell
  static byte heat[NUM_LEDS];

  // Step 1.  Cool down every cell a little
  for ( int i = 0; i < HALF_POS; i++) {
    heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / NUM_LEDS) + 2));
  }
  for ( int i = HALF_POS; i < NUM_LEDS - 1; i++) {
    heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / NUM_LEDS) + 2));
  }

  // Step 2.  Heat from each cell drifts 'up' and diffuses a little
  for ( int k = NUM_LEDS - 1; k >= (HALF_POS); k--) {
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
  }
  for ( int k = 0; k <= (HALF_POS); k++) {
    heat[k] = (heat[k + 1] + heat[k + 2] + heat[k + 2] ) / 3;
  }

  // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
  if ( random8() < SPARKING ) {
    int l = random8(7);
    int r = random8(7);
    heat[HALF_POS + r] = qadd8( heat[HALF_POS + r], random8(160, 255) );
    heat[HALF_POS - l] = qadd8( heat[HALF_POS - l], random8(160, 255) );
  }

  // Step 4.  Map from heat cells to LED colors
  for ( int j = 0; j < NUM_LEDS; j++) {
    CRGB color = HeatColor( heat[j]);
    int pixelnumber;
    if ( gReverseDirection ) {
      pixelnumber = (NUM_LEDS - 1) - j;
    } else {
      pixelnumber = j;
    }
    leds[pixelnumber] = color;
  }


  //FastLED.show(); // display this frame
  FastLED.delay(1000 / FRAMES_PER_SECOND);

}
