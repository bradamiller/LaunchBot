#include <mCore.h>

/**
 * Demonstrate the IR receiver using the remote control that comes with the
 * mBot kit.
 */

MeIR ir;

void setup() {
  ir.begin();
  Serial.begin(115200);
}

void loop() {
  if (ir.decode()) {
    switch (ir.value >> 16 & 0xff) {
      case IR_BUTTON_A:
        Serial.println("Button A");
        break;
      case IR_BUTTON_B:
        Serial.println("Button B");
        break;
      case IR_BUTTON_C:
        Serial.println("Button C");
        break;
    }
  }
}
