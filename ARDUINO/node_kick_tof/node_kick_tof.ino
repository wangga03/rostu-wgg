/*
   rosserial Subscriber Example
   Blinks an LED on callback
*/

#include <ros.h>
#include <std_msgs/UInt16.h>
#include <VL53L0X.h>
#include <Wire.h>

VL53L0X sensor;

int TOF_Read;
int kick = 0;
ros::NodeHandle nh;

void baca_kick_data( const std_msgs::UInt16& kick_data) {
  kick = int(kick_data.data);
  if (kick == 10) { //charging
    digitalWrite(12, HIGH);
    delay(500);
  }
  if (kick == 5) { //stop charging
    digitalWrite(12, LOW);
    delay(500);
    digitalWrite(13, HIGH);
    delay(50);
    digitalWrite(13, LOW);
    delay(200);
  }
  if (kick == 20) { //kick trigger kuat
    digitalWrite(12, LOW);
    delay(500);
    digitalWrite(13, HIGH);
    delay(50);
    digitalWrite(13, LOW);
    delay(200);
    digitalWrite(12, HIGH);
    delay(50);
  }
  if (kick == 30) { //kick trigger lemah
    digitalWrite(12, LOW);
    delay(500);
    digitalWrite(13, HIGH);
    delay(50);
    digitalWrite(13, LOW);
    delay(200);
    digitalWrite(12, HIGH);
    delay(50);
  }
}
//std_msgs::UInt16 tof_data;

ros::Subscriber<std_msgs::UInt16> sub("kick_node", & baca_kick_data);
//ros::Publisher pub_tof("topic_sensor_tof", &tof_data);

void setup()
{
  pinMode(13, OUTPUT); //trigger
  digitalWrite(13, LOW);
  pinMode(12, OUTPUT); //charging
  digitalWrite(12, LOW);
  Wire.begin();
  
  nh.initNode();
  nh.subscribe(sub);
  //nh.advertise(pub_tof);

  sensor.setTimeout(500);
  sensor.init();

#if defined LONG_RANGE
  // lower the return signal rate limit (default is 0.25 MCPS)
  sensor.setSignalRateLimit(0.1);
  // increase laser pulse periods (defaults are 14 and 10 PCLKs)
  sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);
  sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);
#endif

#if defined HIGH_SPEED
  // reduce timing budget to 20 ms (default is about 33 ms)
  sensor.setMeasurementTimingBudget(20000);
#elif defined HIGH_ACCURACY
  // increase timing budget to 200 ms
  sensor.setMeasurementTimingBudget(200000);
#endif
}

void loop()
{
  nh.spinOnce();
  delay(1);

//  TOF_Read = sensor.readRangeSingleMillimeters();
//  tof_data.data = TOF_Read;
//  pub_tof.publish(&tof_data);
}
