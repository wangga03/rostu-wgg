/*
 * 30 degrees = 0.523599 radians
 * 90 degrees = 1.5708 radians
 * 150 degrees = 2,61799 radians
 * 270 degrees = 4,71239 radians
*/
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

float ax;
float ay;
float w;

double dett = (b*f*g) + (e*a*i) + (c*d*h) - (a*f*h) - (b*d*i) - (e*c*g);
double mult = 1/dett;

String x = " ";

void setup() {
  // put your setup code here, to run once:
  pinMode(motor1_CW, OUTPUT);
  pinMode(motor1_CCW, OUTPUT);
  
  pinMode(motor2_CW, OUTPUT);
  pinMode(motor2_CCW, OUTPUT);
  
  pinMode(motor3_CW, OUTPUT);
  pinMode(motor3_CCW, OUTPUT);
  
  pinMode(13, OUTPUT);
  
//  attachInterrupt(0, ai0, RISING);  
//  attachInterrupt(1, ai1, RISING);  
  
  Serial.begin (9600);
}

int f1CW;
int f1CCW;

int f2CW;
int f2CCW;

int f3CW;
int f3CCW;

volatile long temp, counter = 0;

/*void ai0{
  if (digitalRead(encoderA) == LOW){
    counter+0.5;
    }
  else {
    counter-0.5
    }
  }
void ai1{
  if (digitalRead(encoderb) == LOW){
    counter+0.5;
    }
  else {
    counter-0.5;
    }
  }*/
void majuu(){
  Serial.println ("North");
  
  analogWrite(motor1_CW, f1CW);
  analogWrite(motor2_CCW, f2CCW);
  analogWrite(motor3_CCW, f3CCW);
 /* delay(1000);
  delay(1000);*/
  }
void kiri(){
  Serial.println ("North");
  
  analogWrite(motor1_CW, f1CW);
  analogWrite(motor2_CW, f2CW);
  analogWrite(motor3_CCW, f3CCW);
 /* delay(1000);
  delay(1000);*/
  }
void kanan(){
  Serial.println ("North");
  
  analogWrite(motor1_CCW, f1CCW);
  analogWrite(motor2_CCW, f2CCW);
  analogWrite(motor3_CW, f3CW);
 /* delay(1000);
  delay(1000);*/
  }
void CW(){
  Serial.println ("North");
  
  analogWrite(motor1_CCW, f1CCW);
  analogWrite(motor2_CCW, f2CCW);
  analogWrite(motor3_CCW, f3CCW);
 /* delay(1000);
  delay(1000);*/
  }
void CCW(){
  Serial.println ("North");
  
  analogWrite(motor1_CW, f1CW);
  analogWrite(motor2_CW, f2CW);
  analogWrite(motor3_CW, f3CW);
 /* delay(1000);
  delay(1000);*/
  }

double force1;
double force2;
double force3;

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

void loop() {
  // put your main code here, to run repeatedly:
  
  if (Serial.available() > 0){
    
    x = Serial.readString();
    Serial.print(x);
    //majuu
    if (x == "F"){
      digitalWrite(13, HIGH);
      /*ax = 1;
      ay = 0;
      w = 0;
      mathematical();
      majuu();*/
      }

    //kanan
    if (x == "R"){
      ax = 0;
      ay = 1;
      w = 0;
      mathematical();
      kanan();
      }
    
    //kiri  
    if (x == "L"){
      ax = 0;
      ay = -1;
      w = 0;
      mathematical();
      kiri();
      }
      
    //CW
    if (x == "cw"){
      ax = 0;
      ay = 0;
      w = -1;
      mathematical();
      majuu();
      }
      
    //CCW
    if (x == "ccw"){
      ax = 0;
      ay = 0;
      w = 1;
      mathematical();
      majuu();
      }
    }
  }
