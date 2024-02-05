#include <Wire.h>
#include <DFRobot_QMC5883.h>
DFRobot_QMC5883 compass;
 

int pulsea = 2, pulseb = 3,pulsea1 = 18, pulseb1 = 19;
int temp,temp2, counter = 0, counter2 = 0;
float jarak1, jarak2, d1 = 10, keliling=0, pulse = 200, d2 = 5.8 ;
const float phi = 3.142857142857143;

void fullR()
{
  if (digitalRead(pulsea)==LOW)
  counter--;
  else counter ++;
}
void fullL()
{
  if (digitalRead(pulsea1)==LOW)
  counter2--;
  else counter2 ++;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(pulsea,INPUT_PULLUP);
  pinMode(pulseb,INPUT_PULLUP);
  pinMode(pulsea1,INPUT_PULLUP);
  pinMode(pulseb1,INPUT_PULLUP);
 
  attachInterrupt(digitalPinToInterrupt(pulseb), fullR, RISING);
  attachInterrupt(digitalPinToInterrupt(pulseb1), fullL, RISING);

 

  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
    keliling= d2*phi;
    jarak1= (keliling*(counter/pulse));
    keliling= d1*phi;
    jarak2= (keliling*(counter2/pulse));
 
  Serial.print("jarak x :");
  Serial.println(jarak1);
  Serial.print("jarak y : ");
  Serial.println(jarak2);

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
  // Convert to degrees
  float headingDegrees = heading * 180/M_PI; 
  // Output
  Serial.print(" Heading = ");
  Serial.print(heading);
  Serial.print(" Degress = ");
  Serial.print(headingDegrees);
  Serial.println();
  delay(100);
}
