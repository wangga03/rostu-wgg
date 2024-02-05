#include <ros.h>
#include <std_msgs/Float32.h>
#include <std_msgs/UInt16.h>
#include <std_msgs/UInt8.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <math.h>

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

Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);


int kick;
void baca_kick_data( const std_msgs::UInt8& kick_data) {
  kick = kick_data.data;
  if (kick == 10) { //charging
    digitalWrite(28, HIGH);
    delay(500);
  }  
  if (kick == 5) { //stop charging
    digitalWrite(28, LOW);
    delay(500);
    // digitalWrite(32, HIGH);
    // delay(50);
    digitalWrite(30, LOW);
    delay(200);
  }
  if (kick == 20) { //kick trigger kuat
    digitalWrite(28, LOW);
    delay(500);
    digitalWrite(30, HIGH);
    delay(100);
    digitalWrite(30, LOW);
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

  bno.begin();
  delay(1000);

  pinMode(28, OUTPUT);
  pinMode(30, OUTPUT);
  pinMode(pulsea,INPUT_PULLUP);
  pinMode(pulseb,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pulseb), fullR, RISING);
  
  pinMode(PULSEA,INPUT_PULLUP);
  pinMode(PULSEB,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PULSEB), fullO, RISING);
  digitalWrite(28, LOW);
  
  nh.initNode();
  nh.advertise(encoder1);
  nh.advertise(encoder2);
  nh.advertise(magneto);
  nh.subscribe(sub);
}


void loop() {

sensors_event_t orientationData;
bno.getEvent(&orientationData, Adafruit_BNO055::VECTOR_EULER);

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
data_magneto.data = orientationData.orientation.x;
magneto.publish(&data_magneto);

nh.spinOnce();


}
