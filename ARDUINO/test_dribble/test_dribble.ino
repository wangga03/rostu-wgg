#define drb1_cw 20
#define drb1_ccw 21

#define drb2_cw 22
#define drb2_ccw 23

void setup() {
  // put your setup code here, to run once:
  pinMode(drb1_cw, OUTPUT);
  pinMode(drb1_ccw, OUTPUT);

  pinMode(drb2_cw, OUTPUT);
  pinMode(drb2_ccw, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(drb1_ccw, 0);
  delay(1000);
  analogWrite(drb2_cw, 0);
}
