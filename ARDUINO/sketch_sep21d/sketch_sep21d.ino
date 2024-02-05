/*
 * rosserial Servo Control Example
 *
 * This sketch demonstrates the control of hobby R/C servos
 * using ROS and the arduiono
 * 
 * For the full tutorial write up, visit
 * www.ros.org/wiki/rosserial_arduino_demos
 *
 * For more information on the Arduino Servo Library
 * Checkout :
 * http://www.arduino.cc/en/Reference/Servo
 */

#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif

#include <Servo.h> 
#include <ros.h>
#include <std_msgs/Int16.h>

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

float ax;
float ay;
float w;

double dett = (b*f*g) + (e*a*i) + (c*d*h) - (a*f*h) - (b*d*i) - (e*c*g);
double mult = 1/dett;

double force1;
double force2;
double force3;

ros::NodeHandle  nh;

//Servo servo;

void mathematical(){
  force1 = ((((e - f)*mult)*ax) + (((c - b)*mult)*ay) + ((((b*f) - (e*c))*mult)*w));
  force2 = ((((-d + f)*mult)*ax) + (((a - c)*mult)*ay) + (((-(a*f) + (c*d))*mult)*w));
  force3 = ((((d - e)*mult)*ax) + (((b - a)*mult)*ay) + ((((e*a) - (b*d))*mult)*w));
  
  f1CW = map(force1, 0, 0.91, 0, 255);
  f1CCW = map(force1, 0, -0.91, 0, 255);
  
  f2CW = map(force2, 0, 0.91, 0, 255);
  f2CCW = map(force2, 0, -0.91, 0, 255);
  
  f3CW = map(force3, 0, 0.91, 0, 255);
  f3CCW = map(force3, 0, -0.91, 0, 255);
  }

void baca_data_ax(const std_msgs::Int16& data_ax){
  
}/*
void baca_data_ay(const std_msgs::Int16& data_ay){
  
}
void baca_data_aw(const std_msgs::Int16& data_aw){
  
}
*/
ros::Subscriber<std_msgs::Int16> sub("nilai_ax", baca_data_ax);
//ros::Subscriber<std_msgs::Int16> sub("nilai_ay", baca_data_ay);
//ros::Subscriber<std_msgs::Int16> sub("nilai_aw", baca_data_aw);

void setup(){
  pinMode(13, OUTPUT);

  nh.initNode();
  nh.subscribe(sub);

  pinMode(motor1_CW, OUTPUT);
  pinMode(motor1_CCW, OUTPUT);
  
  pinMode(motor2_CW, OUTPUT);
  pinMode(motor2_CCW, OUTPUT);
  
  pinMode(motor3_CW, OUTPUT);
  pinMode(motor3_CCW, OUTPUT);
  
  pinMode(13, OUTPUT);
  
  //Serial.begin (9600);
  //servo.attach(9); //attach it to pin 9
}

void loop(){
  nh.spinOnce();
  delay(1);
}
