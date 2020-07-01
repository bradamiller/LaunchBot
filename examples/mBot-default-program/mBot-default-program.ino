#include <Servo.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include "mCore.h"

MeRGBLed rgb;
MeUltrasonic ultr(PORT_1);
MeLineFollower line(PORT_2);
MeLEDMatrix ledMx;
MeIR ir;
MeBuzzer buzzer;
Me7SegmentDisplay seg;

MeDCMotor MotorL(M1);
MeDCMotor MotorR(M2);

Servo servo;

int moveSpeed = 200;
int minSpeed = 48;
int factor = 23;

#define NTD1 294
#define NTD2 330
#define NTD3 350
#define NTD4 393
#define NTD5 441
#define NTD6 495
#define NTD7 556
#define NTDL1 147
#define NTDL2 165
#define NTDL3 175
#define NTDL4 196
#define NTDL5 221
#define NTDL6 248
#define NTDL7 278
#define NTDH1 589
#define NTDH2 661
#define NTDH3 700
#define NTDH4 786
#define NTDH5 882
#define NTDH6 990
#define NTDH7 112

#define RUN_F 0x01
#define RUN_B 0x01<<1
#define RUN_L 0x01<<2
#define RUN_R 0x01<<3
#define STOP 0
uint8_t motor_sta = STOP;

enum
{
  MODE_A,
  MODE_B,
  MODE_C
};

uint8_t mode = MODE_A;

int LineFollowFlag=0;

void setup()
{
  Stop();
  rgb.setNumber(16);
  rgb.clear();
  rgb.setColor(10, 0, 0);
  buzzer.tone(NTD1, 300); 
  delay(300);
  rgb.setColor(0, 10, 0);
  buzzer.tone(NTD2, 300);
  delay(300);
  rgb.setColor(0, 0, 10);
  buzzer.tone(NTD3, 300);
  delay(300);
  rgb.clear();
  Serial.begin(115200);
  buzzer.noTone();
  ir.begin(); 
}

void loop()
{
  while(1)
  {
    get_ir_command();
    switch (mode)
    {
      case MODE_A:
        modeA();
        break;
      case MODE_B:
        modeB();
        break;
      case MODE_C:
        modeC();
        break;
    }
  }
}

void get_ir_command()
{
  static long time = millis();
  if (ir.decode())
  {
    uint32_t value = ir.value;
    time = millis();
    switch (value >> 16 & 0xff)
    {
      case IR_BUTTON_A:
        moveSpeed = 220;
        mode = MODE_A;
        Stop();
        buzzer.tone(NTD1, 300); 
        rgb.clear();
        rgb.setColor(10, 10, 10);
        break;
      case IR_BUTTON_B:
        moveSpeed = 200;
        mode = MODE_B;
        Stop();
        buzzer.tone(NTD2, 300); 
        rgb.clear();
        rgb.setColor(0, 10, 0);
        break;
      case IR_BUTTON_C:
        mode = MODE_C;
        moveSpeed = 120;
        Stop();
        buzzer.tone(NTD3, 300); 
        rgb.clear();
        rgb.setColor(0, 0, 10);
        break;
      case IR_BUTTON_PLUS:
        motor_sta = RUN_F;
        //buzzer.tone(NTD4, 300); 
        rgb.clear();
        rgb.setColor(10, 10, 0);
        //               Forward();
        break;
      case IR_BUTTON_MINUS:
        motor_sta = RUN_B;
        rgb.clear();
        rgb.setColor(10, 0, 0);
        //buzzer.tone(NTD4, 300); 
        //               Backward();
        break;
      case IR_BUTTON_NEXT:
        motor_sta = RUN_R;
        //buzzer.tone(NTD4, 300); 
        rgb.clear();
        rgb.setColor(1,10, 10, 0);
        //               TurnRight();
        break;
      case IR_BUTTON_PREVIOUS:
        motor_sta = RUN_L;
        //buzzer.tone(NTD4, 300); 
        rgb.clear();
        rgb.setColor(2,10, 10, 0);
        //               TurnLeft();
        break;
      case IR_BUTTON_9:
        buzzer.tone(NTDH2, 300); 
        delay(300);
        ChangeSpeed(factor * 9 + minSpeed);
        break;
      case IR_BUTTON_8:
        buzzer.tone(NTDH1, 300); 
        delay(300);
        ChangeSpeed(factor * 8 + minSpeed);
        break;
      case IR_BUTTON_7:
        buzzer.tone(NTD7, 300); 
        delay(300);
        ChangeSpeed(factor * 7 + minSpeed);
        break;
      case IR_BUTTON_6:
        buzzer.tone(NTD6, 300); 
        delay(300);
        ChangeSpeed(factor * 6 + minSpeed);
        break;
      case IR_BUTTON_5:
        buzzer.tone(NTD5, 300); 
        delay(300);
        ChangeSpeed(factor * 5 + minSpeed);
        break;
      case IR_BUTTON_4:
        buzzer.tone(NTD4, 300); 
        delay(300);
        ChangeSpeed(factor * 4 + minSpeed);
        break;
      case IR_BUTTON_3:
        buzzer.tone(NTD3, 300); 
        delay(300);
        ChangeSpeed(factor * 3 + minSpeed);
        break;
      case IR_BUTTON_2:
        buzzer.tone(NTD2, 300); 
        delay(300);
        ChangeSpeed(factor * 2 + minSpeed);
        break;
      case IR_BUTTON_1:
        buzzer.tone(NTD1, 300); 
        delay(300);
        ChangeSpeed(factor * 1 + minSpeed);
        break;
    }
  }
  else if (millis() - time > 120)
  {
    motor_sta = STOP;
    time = millis();
  }
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

void TurnLeft()
{
  MotorL.run(-moveSpeed/10);
  MotorR.run(moveSpeed);
}

void TurnRight()
{
  MotorL.run(-moveSpeed);
  MotorR.run(moveSpeed/10);
}

void Stop()
{
  rgb.clear();
  MotorL.run(0);
  MotorR.run(0);
}

uint8_t prevState = 0;
void ChangeSpeed(int spd)
{
  buzzer.tone(NTD5, 300); 
  moveSpeed = spd;
}

void modeA()
{
  switch (motor_sta)
  {
    case RUN_F:
      Forward();
      prevState = motor_sta;
      break;
    case RUN_B:
      Backward();
      prevState = motor_sta;
      break;
    case RUN_L:
      TurnLeft();
      prevState = motor_sta;
      break;
    case RUN_R:
      TurnRight();
      prevState = motor_sta;
      break;
    case STOP:
      if(prevState!=motor_sta){
        prevState = motor_sta;
        Stop();
      }
      break;
  }
}

void modeB()
{
  uint8_t d = ultr.distanceCm(50);
  Serial.println(d);
  static long time = millis();
  randomSeed(analogRead(6));
  uint8_t randNumber = random(2);
  if (d > 15 || d == 0)Forward();
  else if (d > 10) {
    switch (randNumber)
    {
      case 0:
        TurnLeft();
        delay(200);
        break;
      case 1:
        TurnRight();
        delay(200);
        break;
    }
  }
  else
  {
    Backward();
    delay(400);
  }
  delay(100);
}

void modeC()
{
  uint8_t val;
  val = line.readSensors();
  if(moveSpeed >230)moveSpeed=230;
  switch (val)
  {
    case S1_IN_S2_IN:
      Forward();
      LineFollowFlag=10;
      break;

    case S1_IN_S2_OUT:
       Forward();
      if (LineFollowFlag>1) LineFollowFlag--;
      break;

    case S1_OUT_S2_IN:
      Forward();
      if (LineFollowFlag<20) LineFollowFlag++;
      break;

    case S1_OUT_S2_OUT:
      if(LineFollowFlag==10) Backward();
      if(LineFollowFlag<10) TurnLeft();
      if(LineFollowFlag>10) TurnRight();
      break;
  }
}
