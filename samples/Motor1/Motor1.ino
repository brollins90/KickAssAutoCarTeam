#include <Wire.h>
#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_DCMotor *drive = AFMS.getMotor(2);
Adafruit_DCMotor *steering = AFMS.getMotor(1);

void setup() {
  AFMS.begin();

  drive->setSpeed(150);
  stop();

  steering->setSpeed(255);
  steerStraight();
}

void loop() {
  goForward();
  steerLeft();
  delay(1000);
  goBackward();
  steerRight();
  delay(1000);
}

void goForward() {
  drive->run(FORWARD);
}

void goBackward() {
  drive->run(BACKWARD);
}

void stop() {
  drive->run(RELEASE);
}

void steerLeft() {
  steering->run(BACKWARD);
}

void steerRight() {
  steering->run(FORWARD);
}

void steerStraight() {
  steering->run(RELEASE);
}

