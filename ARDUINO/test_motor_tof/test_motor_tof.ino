#include <ros.h>
#include <std_msgs/String.h>
#include<std_msgs/UInt16.h>
#include <VL53L0X.h>

ros::NodeHandle  nh;
std_msgs::UInt16 tof_data;

void baca_multi_data( const std_msgs::String& isi_multi_data) {
//  digitalWrite(LED_BUILTIN, HIGH - digitalRead(LED_BUILTIN)); // blink the led
}

ros::Subscriber<std_msgs::String> sub("topic_multi_data", &baca_multi_data);
ros::Publisher pub_tof("topic_sensor_tof", &tof_data);




void setup() {
  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(pub_tof);

}

void loop() {
  // put your main code here, to run repeatedly:
  nh.spinOnce(); 
  tof_data.data = 1;
  pub_tof.publish(&tof_data);
}
