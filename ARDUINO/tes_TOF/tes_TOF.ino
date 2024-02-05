#include <VL53L0X.h>
int TOFread, TOF_Last_Read;

VL53L0X sensor;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  Serial.println("sistem OTW");  

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("sistem OTW");  

  TOFread = sensor.readRangeSingleMillimeters();
  if (TOFread > 500) {
    TOFread = TOF_Last_Read;
  }
  TOF_Last_Read = TOFread;

  if (TOFread < 60) {
    Serial.println(TOFread);

  }
}
