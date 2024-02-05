#include <ros.h>
#include <std_msgs/Float32.h>
#include <Wire.h>
#include <DFRobot_QMC5883.h>
DFRobot_QMC5883 compass;

ros::NodeHandle nh;
std_msgs::Float32 encoder;
std_msgs::Float32 rotary;
std_msgs::Float32 magnet;
std_msgs::Float32 magnet2;

ros::Publisher rencoder("enc1", &encoder);
ros::Publisher rencoder2("enc2", &rotary);
ros::Publisher hmagnet("mgn", &magnet);
ros::Publisher dmagnet("mgn2", &magnet2);

int pulsea = 2, pulseb = 3, PULSEA = 18, PULSEB = 19;
int temp, counter = 0;
int temp2, counter2 = 0;
float jarak1,jarak2, d1 = 10, keliling=0, pulse = 200, d2 = 5.8;
const float phi = 3.142857142857143;

void fullR()
{
  if (digitalRead(pulsea)==LOW)
  counter--;
  else counter ++;
}
void fullO()
{
  if (digitalRead(PULSEA)==LOW)
  counter2--;
  else counter2 ++;
}

float getHeading(){
  Vector norm = compass.readNormalize();
  float heading = atan2(norm.YAxis, norm.XAxis);
  float declinationAngle = (4.0 + (26.0 / 60.0)) / (180 / PI);
  heading += declinationAngle;
  // Correct for heading < 0deg and heading > 360deg
  if (heading < 0){
    heading += 2 * PI;
  }
  if (heading > 2 * PI){
    heading -= 2 * PI;
  }

  return heading;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(pulsea,INPUT_PULLUP);
  pinMode(pulseb,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pulseb), fullR, RISING);
  
 // put your setup code here, to run once:
  pinMode(PULSEA,INPUT_PULLUP);
  pinMode(PULSEB,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PULSEB), fullO, RISING);

  compass.setRange(QMC5883_RANGE_2GA);
  compass.setMeasurementMode(QMC5883_CONTINOUS); 
  compass.setDataRate(QMC5883_DATARATE_50HZ);
  compass.setSamples(QMC5883_SAMPLES_8);
  compass.begin();
  
  nh.initNode();
  nh.advertise(rencoder);
  nh.advertise(rencoder2);
  nh.advertise(hmagnet);
  nh.advertise(dmagnet);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (counter != temp ){
    temp = counter;
    keliling= d2*phi;
    jarak1= (keliling*(counter/pulse));
}
  if (counter2 != temp2 ){
    temp2 = counter2;
    keliling= d1*phi;
    jarak2= (keliling*(counter2/pulse)); 
  }
    
    encoder.data = jarak1;
    rencoder.publish(&encoder);
    rotary.data = jarak2;
    rencoder2.publish(&rotary);
    
  float headingValue = getHeading();
  // Convert to degrees
  float headingDegrees = headingValue * 180/M_PI; 
  // Output

  magnet.data= headingValue;
  hmagnet.publish(&magnet);
  magnet2.data= headingDegrees;
  dmagnet.publish(&magnet2);
  nh.spinOnce();
}
