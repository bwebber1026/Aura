#include <Arduino.h>
//lib_deps = https://github.com/FastLED/FastLED.git
#include <FastLED.h>
// test

#include <ClickEncoder.h>
#include <TimerOne.h>
//#include <MSGEQ7.h>

#define DEBUG true

#define DATA_PIN  7
#define NUM_LEDS 142
//int HALF_POS = (NUM_LEDS * 0.5) - 1;
#define HALF_POS 70
CRGB leds[NUM_LEDS];
//CRGB hues[NUM_LEDS];
#define FRAMES_PER_SECOND  300


// RGB ENCODER SETUP
#define REDPIN    3
#define GREENPIN  5
#define BLUEPIN   6
ClickEncoder *encoder;
int16_t last, value;
int16_t encoderStatus = 1;
void timerIsr() {
  encoder->service();
}

// SPARKING: What chance (out of 255) is there that a new spark will be lit?
// Higher chance = more roaring fire.  Lower chance = more flickery fire.
// Default 120, suggested range 50-200.
#define FRAMES_PER_SECOND 70
bool gReverseDirection = false;
#define COOLING  170
#define SPARKING 10

// MSGEQ7 SETUP and SMOOTHING (eventually replace by MSGEQ7 class?)
#define AUDIO_LEFT_PIN    0 // hammond 0
#define AUDIO_RIGHT_PIN   1 // hammond N/A
#define MSGEQ7_STROBE_PIN 4 // hammond 9
#define MSGEQ7_RESET_PIN  5 // hammond 10
int   filter_min    = 120;
int   left_filter_max, right_filter_max, filter_max    = 1016;
float lowPass_audio = 0.15;
float EQ[7] = {0, 0, 0.1, 0.1, 0.1, 0.1, 0};
int   sensitive_min = filter_min - (filter_min * .15);
float  FILTER_MIN[7] = {filter_min, filter_min, filter_min, filter_min, filter_min, filter_min, filter_min};

//float  EQ[7] = {0, 0, 0, 0, 0, 0, 0};

int   new_left, new_right;
int   prev_value, prev_left, prev_right, left_value, right_value;
int   left[7], right[7], mono[7];
int   left_volume, right_volume, mono_volume;
// for msgeq7 mapping
float left_factor, right_factor, mono_factor, full_factor;
int   mapped_left[7], mapped_right[7], full_mapped[14], mapped[7], full_flex[7];
float half_MAPPED_LEFT_AMP, half_MAPPED_RIGHT_AMP;

int HUEZ[14] = {240, 200, 160, 120, 80, 40, 0, 0, 40, 80, 120, 160, 200, 240};

int zero_l, three_l, six_l, zero_r, three_r, six_r;

int ledindex, half_MAPPED_AMPLITUDE, segment;
float divFactor;

int hue;
int INDEX;

// for mirroring
int current_hue;
int current_brightness;
int next_hue;
int next_brightness;
int pos;
int point;

// more mirroring?
int left_current_brightness;
int right_current_brightness;
int left_next_brightness;
int right_next_brightness;
int left_pos;
int right_pos;
int left_point;
int right_point;
int left_next_hue;
int right_next_hue;
int left_current_sat;
int right_current_sat;
int left_next_sat;
int right_next_sat;

int prev_left_amp;
int prev_right_amp;

// segment sizes
int   segmentSize = 35;
int   half_segmentSize = floor(segmentSize * 0.5);
float non_mirror_divFactor = 1.00 / segmentSize;
//float divFactor = 0.00;
//int segmentEnd[7] = {7, 12, 13, 15, 15, 13, 15};
int segmentEnd[7] = {31, 22, 22, 22, 22, 13, 10};


float HUEcorrection = /*floor(255 / NUM_LEDS);*/ 1.7; // *ALMOST* hue range fits on strip length
float half_HUEcorrection = HUEcorrection * 2;
int   cnt;
int   k;

int spectrumWidth = 36;

static uint16_t x;
static uint16_t y;
static uint16_t dist;

float z = 0.00f;
float scale = 20.00f; //1 - ~4000 (shimmery, zoomed out)
//uint8_t noise[MAX_DIMENSION][MAX_DIMENSION];

//float SPEED = 1.00f;  //1-100 (fast)

//noise stuff
int ioffset;
int joffset;
int i;

//palette stuff
uint8_t maxChanges = 15;      // Value for blending between palettes.
// Forward declarations of an array of cpt-city gradient palettes, and
// a count of how many there are.  The actual color palette definitions
// are at the bottom of this file.
extern const TProgmemRGBGradientPalettePtr gGradientPalettes[];
extern const uint8_t gGradientPaletteCount;
float colorIndex = (256 / float(NUM_LEDS));
// Current palette number from the 'playlist' of color palettes
uint8_t gCurrentPaletteNumber = 0;
CRGBPalette16 gCurrentPalette( CRGB::Black);
CRGBPalette16 gTargetPalette( gGradientPalettes[0] );


int ihue = 0;
int encoderHue = 0;
float fhue = 0.00;
int BRIGHTNESS = 255;
int saturation = 255;

//float SPEED = 1;

int MILLISECONDS;

void setup() {
  delay(500);
  INITIALIZE();
  welcome();
}

void welcome() {
  //intro animation for box button and leds
  delay(500);
}

void loop() {

  EVERY_N_MILLISECONDS(MILLISECONDS) {
    READ_AUDIO();
  }
  MODE();


}
