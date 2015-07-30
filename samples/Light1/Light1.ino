#include <Servo.h>

Servo servo1;

void setup() {
  servo1.attach(10);
}

void loop() {
  int light = analogRead(0);
  int normalized = map(light, 0, 1023, 0, 100);
  servo1.write(normalized);
}
