#include <mCore.h>

/**
 * Demonstrate the Line Tracking sensor that comes with the mBot kit.
 * Should be able to not only track lines, but work as a cliff sensor (on/off the table)
 * You can verify the operation of the sensor by 
 */

MeLineFollower lf(PORT_2);

void setup() {
  Serial.begin(115200);
}

void loop() {
  int sensorState = lf.readSensors();
  switch(sensorState)
  {
    case S1_IN_S2_IN: Serial.println("Sensor 1 and 2 are inside of black line"); break;
    case S1_IN_S2_OUT: Serial.println("Sensor 2 is outside of black line"); break;
    case S1_OUT_S2_IN: Serial.println("Sensor 1 is outside of black line"); break;
    case S1_OUT_S2_OUT: Serial.println("Sensor 1 and 2 are outside of black line"); break;
    default: break;
  }
  delay(200);

}
