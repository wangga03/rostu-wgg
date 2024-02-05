#include <ros.h>
#include <std_msgs/Float32.h>

ros::NodeHandle nh;
std_msgs::Float32 encoder;
std_msgs::Float32 rotary;

ros::Publisher rencoder("enc1", &encoder);
ros::Publisher rencoder2("enc2", &rotary);

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

void setup() {
  // put your setup code here, to run once:
  pinMode(pulsea,INPUT_PULLUP);
  pinMode(pulseb,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pulseb), fullR, RISING);
  
 // put your setup code here, to run once:
  pinMode(PULSEA,INPUT_PULLUP);
  pinMode(PULSEB,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PULSEB), fullO, RISING);
  
  nh.initNode();
  nh.advertise(rencoder);
  nh.advertise(rencoder2);
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
    nh.spinOnce();
}




  
  
