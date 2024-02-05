/*
   rosserial Subscriber Example
   Blinks an LED on callback
*/

#include <ros.h>
#include <std_msgs/UInt16.h>

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

ros::Subscriber<std_msgs::UInt16> sub("kick_node", & baca_kick_data);

void setup()
{
  pinMode(13, OUTPUT); //trigger
  digitalWrite(13, LOW);
  pinMode(12, OUTPUT); //charging
  digitalWrite(12, LOW);
  nh.initNode();
  nh.subscribe(sub);
}

void loop()
{
  nh.spinOnce();
  delay(1);
}
