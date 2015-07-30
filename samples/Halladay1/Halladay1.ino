#include <Wire.h>
#include <Adafruit_MotorShield.h>

#define PIN_LIGHT   0
#define PIN_PROX    1

#define TIME_STOP     500
#define TIME_BACKUP   300
#define TIME_REDIRECT (TIME_BACKUP+200)

#define LIGHT_WHITE_THRESHOLD 200

#define LEFT   0
#define RIGHT  1

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_DCMotor *drive = AFMS.getMotor(2);
Adafruit_DCMotor *steering = AFMS.getMotor(1);

void setup() {
  
  AFMS.begin();

  drive->setSpeed(150);
  moveStop();

  steering->setSpeed(255);
  goStraight();

  moveForward();
}

void loop() {
  if (isWhite()){
    moveStop();
    int left = tryLeftBackup();
    int right = tryRightBackup();
    if (left > right) {
      goLeft();
    } else {
      goRight();
    }
    moveBackward();
    delay(TIME_REDIRECT);
    goStraight();
    moveForward();    
  }
}

int completeBackup() {
  int startTime = millis();
  moveBackward();
  while(isWhite());
  delay(TIME_BACKUP);
  goStraight();
  moveForward();
  while(!isWhite());
  moveStop();
  return (int) (millis() - startTime);
}

int tryLeftBackup() {
  goLeft();
  return completeBackup();
}

int tryRightBackup() {
  goRight();
  return completeBackup();
}

void goLeft() {
  steering->run(BACKWARD);
}

void goRight() {
  steering->run(FORWARD);
}

void goStraight() {
  steering->run(RELEASE);
}

#define DS_STOPPED  0
#define DS_FORWARD  1
#define DS_BACKWARD 2
int driveState = DS_STOPPED;

int getDistance() {
  return analogRead(PIN_PROX);
}

int isWhite() {
  return (analogRead(PIN_LIGHT) < LIGHT_WHITE_THRESHOLD);
}

void moveForward() {
  drive->run(FORWARD);
  driveState = DS_FORWARD;
}

void moveBackward() {
  drive->run(BACKWARD);
  driveState = DS_BACKWARD;
}

void moveStop() {
  if (driveState == DS_FORWARD) {
    drive->run(BACKWARD);
    delay(TIME_STOP);
  } else if (driveState == DS_BACKWARD) {
    drive->run(FORWARD);
    delay(TIME_STOP);
  }
  drive->run(RELEASE);
  driveState = DS_STOPPED;
}
