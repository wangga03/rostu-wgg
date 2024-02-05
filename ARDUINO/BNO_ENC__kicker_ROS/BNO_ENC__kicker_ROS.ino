#include <ros.h>
#include <std_msgs/Float32.h>
#include <std_msgs/UInt16.h>
#include <std_msgs/UInt8.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <math.h>

//BNO Variable
float theta;

float thetaRad;
float phiRad;

float Xm;
float Ym;
float psi;

//encoder variable
int pulsea = 2, pulseb = 3, PULSEA = 18, PULSEB = 19;
int temp, counter = 0;
int temp2, counter2 = 0;
float jarak1,jarak2, d1 = 10, keliling=0, pulse = 200, d2 = 5.8;
const float phi = 3.142857142857143;


//publish initiate
ros::NodeHandle nh;
std_msgs::Float32 data_magneto;
std_msgs::Float32 data_encoder1;
std_msgs::Float32 data_encoder2;

//publish command
ros::Publisher magneto("mag", &data_magneto);
ros::Publisher encoder1("enc1", &data_encoder1);
ros::Publisher encoder2("enc2", &data_encoder2);

#define BNO055_SAMPLERATE_DELAY_MS (100) 

Adafruit_BNO055 myIMU = Adafruit_BNO055();


int kick;
void baca_kick_data( const std_msgs::UInt8& kick_data) {
  kick = int(kick_data.data);
  if (kick == 10) { //charging
    digitalWrite(30, HIGH);
    delay(500);
  }  
  if (kick == 5) { //stop charging
    digitalWrite(30, LOW);
    delay(500);
    // digitalWrite(32, HIGH);
    // delay(50);
    digitalWrite(32, LOW);
    delay(200);
  }
  if (kick == 20) { //kick trigger kuat
    digitalWrite(30, LOW);
    delay(500);
    digitalWrite(32, HIGH);
    delay(100);
    digitalWrite(32, LOW);
    delay(200);

  }

}

ros::Subscriber<std_msgs::UInt8> sub("topic_kick", & baca_kick_data);

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


void setup() {

  myIMU.begin() ;
  delay(1000);
  int8_t temp=myIMU.getTemp() ;
  //Serial.println(temp);
  myIMU.setExtCrystalUse(true);

  pinMode(pulsea,INPUT_PULLUP);
  pinMode(pulseb,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pulseb), fullR, RISING);
  
  pinMode(PULSEA,INPUT_PULLUP);
  pinMode(PULSEB,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PULSEB), fullO, RISING);
  
  nh.initNode();
  nh.advertise(encoder1);
  nh.advertise(encoder2);
  nh.advertise(magneto);
  nh.subscribe(sub);
}


void loop() {

imu::Vector<3> mag =myIMU.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER) ;

phiRad=phi/360*(2*3.14);
thetaRad=theta/360*(2*3.14);

Xm=mag.x()*cos(thetaRad)-mag.y()*sin(phiRad)*sin(thetaRad)+mag.z()*cos(phiRad)*sin(thetaRad);
Ym=mag.y()*cos(phiRad)+mag.z()*sin(phiRad);

psi=atan2(Ym,Xm)/(2*3.14)*360;

if(psi<0)
  psi+=360;
if(psi>360)
  psi-=360;

 


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
    
data_encoder1.data = jarak1;
encoder1.publish(&data_encoder1);
data_encoder2.data = jarak2;
encoder2.publish(&data_encoder2);
data_magneto.data = psi;
magneto.publish(&data_magneto);

nh.spinOnce();

delay(BNO055_SAMPLERATE_DELAY_MS) ;
}
