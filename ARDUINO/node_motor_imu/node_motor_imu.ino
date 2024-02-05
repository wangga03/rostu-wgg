/*
   rosserial Subscriber Example
   Blinks an LED on callback
*/

#include <ros.h>
#include <std_msgs/String.h>
#include<std_msgs/Int16.h>

#define motor2_CW 5
#define motor2_CCW 6

#define motor1_CW 7
#define motor1_CCW 8

#define motor3_CW 9
#define motor3_CCW 10

float radian30 = 0.523599; // alpha 1
float radian90 = 1.5708; //   phi/2
float radian150 = 2.61799; // alpha 2
float radian270 = 4.71239; // alpha 3

float a = sin (radian30 + radian90);  //m11
float b = sin (radian150 + radian90); //m12
float c = sin (radian270 + radian90); //m13
float d = cos (radian30 + radian90);  //m21
float e = cos (radian150 + radian90); //m22
float f = cos (radian270 + radian90); //m23

int g = 1; //m31
int h = 1; //m32
int i = 1; //m33

int f1CW;
int f1CCW;

int f2CW;
int f2CCW;

int f3CW;
int f3CCW;

int TOF_Read;

float ax;
float ay;
float w;

double dett = (b*f*g) + (e*a*i) + (c*d*h) - (a*f*h) - (b*d*i) - (e*c*g);
double mult = 1 / dett;
double force1;
double force2;
double force3;

ros::NodeHandle  nh;
float dataax = 0;
float dataay = 0;
float dataaw = 0;
String isi_multi_data_c;
void baca_multi_data( const std_msgs::String& isi_multi_data) {

  isi_multi_data_c = (isi_multi_data.data);
  dataax = (getValue(isi_multi_data_c, ' ', 0)).toFloat();
  dataay = (getValue(isi_multi_data_c, ' ', 1)).toFloat();
  dataaw = (getValue(isi_multi_data_c, ' ', 2)).toFloat();

  //  digitalWrite(LED_BUILTIN, HIGH - digitalRead(LED_BUILTIN)); // blink the led
}

void mathematical() {
  ax = dataax;
  ay = dataay;
  w = dataaw;

  force1 = ((((e - f) * mult) * ax) + (((c - b) * mult) * ay) + ((((b * f) - (e * c)) * mult) * w));
  force2 = ((((-d + f) * mult) * ax) + (((a - c) * mult) * ay) + (((-(a * f) + (c * d)) * mult) * w));
  force3 = ((((d - e) * mult) * ax) + (((b - a) * mult) * ay) + ((((e * a) - (b * d)) * mult) * w));

  if (force1 >= 0) {
    f1CW = map(force1, 0, 0.91, 0, 255);
    f1CCW = 0;
  }

  if (force1 < 0) {
    f1CW = 0;
    f1CCW = map(force1, 0, -0.91, 0, 255);
  }

  if (force2 >= 0) {
    f2CW = map(force2, 0, 0.91, 0, 255);
    f2CCW = 0;
  }

  if (force2 < 0) {
    f2CW = 0;
    f2CCW = map(force2, 0, -0.91, 0, 255);
  }

  if (force3 >= 0) {
    f3CW = map(force3, 0, 0.91, 0, 255);
    f3CCW = 0;
  }

  if (force3 < 0) {
    f3CW = 0;
    f3CCW = map(force3, 0, -0.91, 0, 255);
  }
  //f1CW = map(force1, 0, 0.91, 0, 255);
  //f1CCW = map(force1, 0, -0.91, 0, 255);

  //f2CW = map(force2, 0, 0.91, 0, 255);
  //f2CCW = map(force2, 0, -0.91, 0, 255);

  //f3CW = map(force3, 0, 0.91, 0, 255);
  //f3CCW = map(force3, 0, -0.91, 0, 255);
}

//std_msgs::Int16 imu_data;

ros::Subscriber<std_msgs::String> sub("topic_multi_data", baca_multi_data);
//ros::Publisher pub_imu("topic_sensor_imu", &imu_data);

String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }

  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void setup()
{
  //pinMode(LED_BUILTIN, OUTPUT);
  nh.initNode();
  nh.subscribe(sub);
  //nh.advertise(pub_imu);
//  
//  Wire.begin();
//  mpu.begin();
//  delay(1000);
//  mpu.calcOffsets();

  pinMode(motor1_CW, OUTPUT);
  pinMode(motor1_CCW, OUTPUT);

  pinMode(motor2_CW, OUTPUT);
  pinMode(motor2_CCW, OUTPUT);

  pinMode(motor3_CW, OUTPUT);
  pinMode(motor3_CCW, OUTPUT);
}

void loop()
{
  mathematical();
  analogWrite(motor1_CCW, f1CCW);
  analogWrite(motor1_CW, f1CW);
  analogWrite(motor2_CCW, f2CCW);
  analogWrite(motor2_CW, f2CW);
  analogWrite(motor3_CCW, f3CCW);
  analogWrite(motor3_CW, f3CW);
//
//  mpu.update();
//  imu_data.data = mpu.getAngleZ()*100;
//  pub_imu.publish(&imu_data);
  
  nh.spinOnce();
  delay(1);
}
