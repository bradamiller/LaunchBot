#ifndef MEPORT_H_
#define MEPORT_H_

#include <Arduino.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include "wiring_private.h"
#include "pins_arduino.h"
#ifndef F_CPU
#define  F_CPU 16000000UL
#endif
#include <util/delay.h>
#include <stdint.h>
#include <stdlib.h>
#include <Wire.h>
#include <SoftwareSerial.h>

typedef enum
{
    MeBaseBoard,
    MakeblockOrion,
    mCore,
    UNOShield
}Board_type;

extern Board_type MakeblockBoard;

typedef struct
{
    uint8_t s1;
    uint8_t s2;
} MePort_Sig;
extern MePort_Sig mePort[11];//mePort[0] is nonsense

#define NC 					0377

// MePort_Sig mePort[11]={{NC, NC}, {11, 12}, {9, 10}, {A2, A3}, {A0, A1},
//     {NC, NC}, {NC, NC}, {NC, NC}, {NC, NC}, {6, 7}, {5, 4}};

// #define PORT_1 				0x01
// #define PORT_2 				0x02
// #define PORT_3 				0x03
// #define PORT_4 				0x04
// #define PORT_5 				0x05
// #define PORT_6 				0x06
// #define PORT_7 				0x07
// #define PORT_8 				0x08
// #define M1     				0x09
// #define M2     				0x0a

typedef enum
{
    PORT_0,
    PORT_1,
    PORT_2,
    PORT_3,
    PORT_4,
    PORT_5,
    PORT_6,
    PORT_7,
    PORT_8,
    M1,
    M2,
}MEPORT;
// #endif

#define SLOT1 1
#define SLOT2 2
#define SLOT_1 SLOT1
#define SLOT_2 SLOT2

#define FALSE 0
#define TRUE  1

///@brief class of MePort,it contains two pin.
class MePort
{
public:
    MePort();
    ///@brief initialize the Port
    ///@param port port number of device
    MePort(uint8_t port);
    MePort(uint8_t port,uint8_t slot);
    ///@return the level of pin 1 of port
    ///@retval true on HIGH.
    ///@retval false on LOW.
    uint8_t getPort();
    uint8_t getSlot();
    ///@return the level of pin 1 of port
    ///@retval true on HIGH.
    ///@retval false on LOW.
    bool dRead1();
    ///@return the level of pin 2 of port
    ///@retval true on HIGH.
    ///@retval false on LOW.
    bool dRead2();
    ///@brief set the analog value of pin 1 of port
    ///@param value is HIGH or LOW
    void dWrite1(bool value);
    ///@brief set the level of pin 1 of port
    ///@param value is HIGH or LOW
    void dWrite2(bool value);
    ///@return the analog signal of pin 1 of port between 0 to 1023
    int aRead1();
    ///@return the analog signal of pin 2 of port between 0 to 1023
    int aRead2();
    ///@brief set the PWM outpu value of pin 1 of port
    ///@param value between 0 to 255
    void aWrite1(int value);
    ///@brief set the PWM outpu value of pin 2 of port
    ///@param value between 0 to 255
    void aWrite2(int value);
    void reset(uint8_t port);
    void reset(uint8_t port,uint8_t slot);
    uint8_t pin1();
    uint8_t pin2();
    uint8_t pin();
    uint8_t pin(uint8_t port,uint8_t slot);
protected:
    uint8_t s1;
    uint8_t s2;
    uint8_t _port;
    uint8_t _slot;
};

#endif
