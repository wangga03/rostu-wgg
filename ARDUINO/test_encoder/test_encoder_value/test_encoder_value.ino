int pulsea = 1, pulseb=2, pulsez= 3; 

void setup() {
  Serial.begin(9600);
  pinMode(pulsea,INPUT);
  pinMode(pulseb,INPUT);
  pinMode(pulsez,INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  int a,b,z;
  a = digitalRead(pulsea);
  b = digitalRead(pulseb);
  z = digitalRead(pulsez);

  Serial.print(a);
  Serial.print(" , ");
  Serial.print(b);
  Serial.print(" , ");
  Serial.println(z);
}
