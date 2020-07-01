#include <mCore.h>

/*
 * Runs the drive motors forward then backwards repeatedly to verify
 * that they are both working.
 */

MeDCMotor MotorL(M1);
MeDCMotor MotorR(M2);

const int moveSpeed = 200;

void setup() {
}

void Forward()
{
  MotorL.run(-moveSpeed);
  MotorR.run(moveSpeed);
}

void Backward()
{
  MotorL.run(moveSpeed);
  MotorR.run(-moveSpeed);
}


void loop() {
  Forward();
  delay(1000);
  Backward();
  delay(1000);
}
