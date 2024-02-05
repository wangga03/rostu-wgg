#define motor2_CW 5
#define motor2_CCW 6

#define motor1_CW 7
#define motor1_CCW 8

#define motor3_CW 9
#define motor3_CCW 10

#define db1_cw 20
#define db1_ccw 21 // yg dipake

#define db2_cw 22 //yg dipake
#define db2_ccw 23

int spe;

void setup() {
  // put your setup code here, to run once:

  pinMode(motor1_CW, OUTPUT);
  pinMode(motor1_CCW, OUTPUT);

  pinMode(motor2_CW, OUTPUT);
  pinMode(motor2_CCW, OUTPUT);

  pinMode(motor3_CW, OUTPUT);
  pinMode(motor3_CCW, OUTPUT);

  pinMode(db1_cw, OUTPUT);
  pinMode(db1_ccw, OUTPUT);

  pinMode(db2_cw, OUTPUT);
  pinMode(db2_ccw, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  spe = 255 * 0.7;
//  analogWrite(motor1_CW, spe);
//  delay(3000);
//  analogWrite(motor1_CW, 0);
//  analogWrite(motor1_CCW, spe);
//  delay(3000);
//  analogWrite(motor1_CCW, 0);
//
//  analogWrite(motor2_CW, spe);
//  delay(3000);
//  analogWrite(motor2_CW, 0);
//  analogWrite(motor2_CCW, spe);
//  delay(3000);
//  analogWrite(motor2_CCW, 0);
//
//  analogWrite(motor3_CW, spe);
//  delay(3000);
//  analogWrite(motor3_CW, 0);
//  analogWrite(motor3_CCW, spe);
//  delay(3000);
//  analogWrite(motor3_CCW, 0);

  // Ke dalem
  analogWrite(db1_ccw, spe);
  analogWrite(db2_cw, spe);
  delay(3000);
  
  analogWrite(db1_ccw, 0);
  analogWrite(db2_cw, 0);
  delay(3000);

  // Ke luar
  analogWrite(db1_cw, spe);
  analogWrite(db2_ccw, spe);
  
  delay(3000);
  analogWrite(db1_cw, 0);
  analogWrite(db2_ccw, 0);
  delay(3000);
}
