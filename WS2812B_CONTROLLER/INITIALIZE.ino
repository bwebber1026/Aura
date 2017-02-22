#include <Arduino.h>

void INITIALIZE() {
  InitSerial();
  InitWS2812B();
  InitRGBEncoder();
  InitMSGEQ7();
  InitNoise();
}

// wake up the MSGEQ7
void InitMSGEQ7() {
  analogReference(DEFAULT);              // change
  pinMode(MSGEQ7_RESET_PIN,  OUTPUT);
  pinMode(MSGEQ7_STROBE_PIN, OUTPUT);
  pinMode(AUDIO_LEFT_PIN,   INPUT);
  pinMode(AUDIO_RIGHT_PIN,  INPUT);
  digitalWrite(MSGEQ7_RESET_PIN, LOW);
  digitalWrite(MSGEQ7_STROBE_PIN, LOW);
  //RESET MSGEQ7
  digitalWrite(MSGEQ7_RESET_PIN,  HIGH);
  delay(1);
  digitalWrite(MSGEQ7_RESET_PIN,  LOW);
  digitalWrite(MSGEQ7_STROBE_PIN, HIGH);
  delay(1);
}
void InitSerial() {
#ifdef DEBUG
  Serial.begin(115200);
  delay(500);
#endif
}

void InitWS2812B() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalSMD5050);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.setTemperature(Candle);

  for (int i = 0; i < NUM_LEDS; i++) {
    fill_solid(leds, NUM_LEDS, CRGB::Black);
  }
  FastLED.show();
  FastLED.delay(100);
}

void InitRGBEncoder() {
  //12 BIT ENCODER
  encoder = new ClickEncoder(A2, A1, 3, 4);
  //ClickEncoder(ROT_A, ROT_B, SWITCH, RESOLUTION);
  Timer1.initialize(1000);
  Timer1.attachInterrupt(timerIsr);
  encoder->setAccelerationEnabled(true);
  last = -1;
  //COMMON ANODE RGB LED
  pinMode(REDPIN,   OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN,  OUTPUT);
  showAnalogRGB(CRGB::Black);
}

void InitNoise() {
  x = random16();
  y = random16();
  z = random16();
  dist = random16(12345);
}
