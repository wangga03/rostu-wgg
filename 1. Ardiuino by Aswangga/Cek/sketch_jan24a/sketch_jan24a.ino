#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/UInt16.h>

String isi_multi_data_c;
float dataax;
float dataay;
float dataaw;
 float ax, ay, w;

float radian30 = 0.523599; // alpha 1
float radian90 = 1.5708; // phi/2
float radian150 = 2.61799; // alpha 2
float radian270 = 4.71239; // alpha 3

float a = sin (radian30 + radian90); //m11
float b = sin (radian150 + radian90); //m12
float c = sin (radian270 + radian90); //m13
float d = cos (radian30 + radian90); //m21
float e = cos (radian150 + radian90); //m22
float f = cos (radian270 + radian90); //m23

int g = 1; //m31
int h = 1; //m32
int i = 1; //m33

double dett = (b*f*g) + (e*a*i) + (c*d*h) - (a*f*h) - (b*d*i) - (e*c*g);
double mult = 1 / dett;
double force1;
double force2;
double force3;

int f1CW;
int f1CCW;

int f2CW;
int f2CCW;

int f3CW;
int f3CCW;

int db1CW;
int db1CCW;

int db2CW;
int db2CCW;

void multiDataCallback(const std_msgs::String& msg);

ros::NodeHandle nh;

std_msgs::String str_msg;
ros::Subscriber<std_msgs::String> sub_multi_data("topic_multi_data2", &multiDataCallback);

void multiDataCallback(const std_msgs::String& isi_multi_data) {
  // Implement your code to handle data from 'topic_multi_data'
  // Example: Extract and print data
//  nh.loginfo("Received Multi-Data: %s", msg.data);
//float isi_multi_data_c;


  isi_multi_data_c = (isi_multi_data.data);
  dataax = (getValue(isi_multi_data_c, ' ', 0)).toFloat();
  dataay = (getValue(isi_multi_data_c, ' ', 1)).toFloat();
  dataaw = (getValue(isi_multi_data_c, ' ', 2)).toFloat();

  String dataax_str = String(dataax, 2);  // Menggunakan dua digit di belakang koma
  String dataay_str = String(dataay, 2);
  String dataaw_str = String(dataaw, 2);
//
Serial.print("Data AX: ");
  Serial.println(dataax_str);
  Serial.print("Data AY: ");
  Serial.println(dataay_str);
  Serial.print("Data AW: ");
  Serial.println(dataaw_str);

  delay(1000);



}
//
//void kickCallback(const std_msgs::UInt16& msg) {
//  // Implement your code to handle data from 'kick_node'
//  // Example: Extract and print data
//  nh.loginfo("Received Kick Node Trigger: %d", msg.data);
//}

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

//void mathematical() {


//  ax = dataax;
//  ay = dataay;
//  w = dataaw;
//
//  force1 = ((((e - f) * mult) * ax) + (((c - b) * mult) * ay) + ((((b * f) - (e * c)) * mult) * w));
//  force2 = ((((-d + f) * mult) * ax) + (((a - c) * mult) * ay) + (((-(a * f) + (c * d)) * mult) * w));
//  force3 = ((((d - e) * mult) * ax) + (((b - a) * mult) * ay) + ((((e * a) - (b * d)) * mult) * w));
//
//  String force1_str = String(force1, 2);  // Menggunakan dua digit di belakang koma
//  String force2_str = String(force2, 2);
//  String force3_str = String(force3, 2);
//Serial.print("force1: ");
//  Serial.println(force1_str);
//  Serial.print("force2: ");
//  Serial.println(force2_str);
//  Serial.print("force3: ");
//  Serial.println(force3_str);

//  delay(2000);
//
//  if (force1 >= 0) {
//    f1CW = map(force1, 0, 0.91, 0, 255);
//    f1CCW = 0;
//  }
//
//  if (force1 < 0) {
//    f1CW = 0;
//    f1CCW = map(force1, 0, -0.91, 0, 255);
//  }
//
//  if (force2 >= 0) {
//    f2CW = map(force2, 0, 0.91, 0, 255);
//    f2CCW = 0;
//  }
//
//  if (force2 < 0) {
//    f2CW = 0;
//    f2CCW = map(force2, 0, -0.91, 0, 255);
//  }
//
//  if (force3 >= 0) {
//    f3CW = map(force3, 0, 0.91, 0, 255);
//    f3CCW = 0;
//  }
//
//  if (force3 < 0) {
//    f3CW = 0;
//    f3CCW = map(force3, 0, -0.91, 0, 255);
//  }
  //f1CW = map(force1, 0, 0.91, 0, 255);
  //f1CCW = map(force1, 0, -0.91, 0, 255);

  //f2CW = map(force2, 0, 0.91, 0, 255);
  //f2CCW = map(force2, 0, -0.91, 0, 255);

  //f3CW = map(force3, 0, 0.91, 0, 255);
  //f3CCW = map(force3, 0, -0.91, 0, 255);
//}
void setup() {
  Serial.begin(9600);
  nh.initNode();
  nh.subscribe(sub_multi_data);
//  nh.subscribe(sub_kick);
}

void loop() {
  
  nh.spinOnce();
  delay(10);
}
