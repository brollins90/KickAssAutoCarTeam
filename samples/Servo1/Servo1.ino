#include<Servo.h>

Servo servo1;

void setup() {
  servo1.attach(10);
}

void loop() {
  servo1.write(0);
  delay(1000);
  servo1.write(100);
}
