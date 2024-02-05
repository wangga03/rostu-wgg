#include <ros.h>
#include <std_msgs/Float32.h>
#include <std_msgs/UInt16.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

unsigned long timer = 0;

ros::NodeHandle nh;

std_msgs::Float32 data_uji_coba;
std_msgs::Float32 encoder1;
std_msgs::Float32 encoder2;


ros::Publisher chatter("chatter", &data_uji_coba);
ros::Publisher encode1("enc1", &encoder1);
ros::Publisher encode2("enc2", &encoder2);

//float trying = 1.023;/
int temp, counter = 0; //This variable will increase or decrease depending on the rotation of encoder1
int temp2, counter2 = 0; //This variable will increase or decrease depending on the rotation of encoder1

float jarak1, jarak2, d1 = 10, keliling=0, pulse = 200, d2 = 5.8000;
const float phi = 3.142857142857143;

int kick =0;

void ai0() {
  // ai0 is activated if DigitalPin nr 2 is going from LOW to HIGH
  // Check pin 3 to determine the direction
  if(digitalRead(18)==LOW) {
  counter2--;
  }else{
  counter2++;
  }
}
   
void ai1() {
  // ai0 is activated if DigitalPin nr 3 is going from LOW to HIGH
  // Check with pin 2 to determine the direction
  if(digitalRead(2)==LOW) {
  counter--;
  }else{
  counter++;
  }
}

void baca_kick_data( const std_msgs::UInt16& kick_data) {
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
//    digitalWrite(30, HIGH);
//    delay(50);
  }
  if (kick == 30) { //kick trigger lemah
    digitalWrite(30, LOW);
    delay(500);
    digitalWrite(32, HIGH);
    delay(100);
    digitalWrite(32, LOW);
    delay(200);
//    digitalWrite(30, HIGH);
//    delay(50);
  }
}


float theta;
float phiI;

float thetaRad;
float phiRad;

float Xm;
float Ym;
float psi;

#define BNO055_SAMPLERATE_DELAY_MS (100) 

Adafruit_BNO055 myIMU = Adafruit_BNO055();

ros::Subscriber<std_msgs::UInt16> sub("kick_node2", & baca_kick_data);

void setup()
{
  nh.initNode();
  nh.advertise(chatter);
  nh.advertise(encode1);
  nh.advertise(encode2);

  pinMode(32, OUTPUT); //the trigger kick
  pinMode(30, OUTPUT);
  digitalWrite(32, LOW);
  digitalWrite(30, LOW);
  nh.subscribe(sub);



  pinMode(2, INPUT_PULLUP); // internal pullup input pin 2 
  pinMode(3, INPUT_PULLUP); // internal pullup input pin 3

  pinMode(18, INPUT_PULLUP); // internal pullup input pin 20 
  pinMode(19, INPUT_PULLUP); // internal pullup input pin 21  
  
  attachInterrupt(1, ai1, RISING);
  attachInterrupt(4, ai0, RISING);

  Serial.begin (115200) ;
myIMU.begin() ;
delay(1000);
int8_t temp=myIMU.getTemp() ;

Serial.println(temp);
myIMU.setExtCrystalUse(true);

}

void loop()
{
  

  if( counter != temp ){
    
    temp = counter;
    keliling = d1*phi ;
    jarak1 = ((keliling*(counter/pulse)));
  }

  if( counter2 != temp2 ){
    
    temp2 = counter2;
    keliling = d2*phi ;
    jarak2 = ((keliling*(counter2/pulse)));
  }

imu::Vector<3> acc =myIMU.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER) ;
imu::Vector<3> gyro =myIMU.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE) ;
imu::Vector<3> mag =myIMU.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER) ;

phiRad=phiI/360*(2*3.14);
thetaRad=theta/360*(2*3.14);

Xm=mag.x()*cos(thetaRad)-mag.y()*sin(phiRad)*sin(thetaRad)+mag.z()*cos(phiRad)*sin(thetaRad);
Ym=mag.y()*cos(phiRad)+mag.z()*sin(phiRad);

psi=atan2(Ym,Xm)/(2*3.14)*360;

// Serial.print(acc.x());
// Serial.print(",");
// Serial.print(acc.y());
// Serial.print(",");
// Serial.print(acc.z());
// Serial.print(",");

// Serial.print(gyro.x());
// Serial.print(",");
// Serial.print(gyro.y());
// Serial.print(",");
// Serial.print(gyro.z());
// Serial.print(",");

// Serial.print(mag.x());
// Serial.print(",");
// Serial.print(mag.y());
// Serial.print(",");
//Serial.println(mag.z());
//double yaw = atan2(mag.y(),mag.x())*180/PI;

//Serial.println(yaw);

Serial.println(psi);

delay(BNO055_SAMPLERATE_DELAY_MS) ;

  encoder1.data = jarak1;
  encoder2.data = jarak2;
  

  chatter.publish( &data_uji_coba );
  encode1.publish(&encoder1);
  encode2.publish(&encoder2);
  nh.spinOnce();
  delay(10);
}
