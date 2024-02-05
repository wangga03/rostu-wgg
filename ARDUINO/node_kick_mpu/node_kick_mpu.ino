/*
   rosserial Subscriber Example
   Blinks an LED on callback
*/

#include <ros.h>
#include <std_msgs/UInt16.h>
#include "Wire.h"
#include <MPU6050_light.h>

MPU6050 mpu(Wire);
unsigned long timer = 0;

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
std_msgs::Float32 imu_data;

ros::Subscriber<std_msgs::UInt16> sub("kick_node", & baca_kick_data);
ros::Publisher pub_imu("topic_sensor_imu", &imu_data);

void setup()
{
  pinMode(13, OUTPUT); //trigger
  digitalWrite(13, LOW);
  pinMode(12, OUTPUT); //charging
  digitalWrite(12, LOW);
  nh.initNode();
  nh.subscribe(sub);

  Wire.begin();
  byte status = mpu.begin();
  delay(1000);
  mpu.calcOffsets();
}

void loop()
{
  mpu.update();
  imu_data.data = mpu.getAngleZ();
  pub_imu.publish(&imu_data);
  nh.spinOnce();
  delay(1);
}
