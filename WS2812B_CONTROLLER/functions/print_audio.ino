#include <Arduino.h>

void print_audio() {
  READ_AUDIO();
  for (int band = 0; band < 7; band++) {
    Serial.print(mono[band]);
    Serial.print("\t");
  }
  Serial.println();
}
