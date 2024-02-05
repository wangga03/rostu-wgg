int pulsea = 8, pulseb = 9;
int temp, counter = 0;
float jarak, d1 = 10, keliling=0, pulse = 200, d2 = 5.8;
const float phi = 3.142857142857143;

void fullR()
{
  if (digitalRead(pulsea)==LOW)
  counter--;
  else counter ++;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(pulsea,INPUT_PULLUP);
  pinMode(pulseb,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pulseb), fullR, RISING);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (counter != temp ){
    temp = counter;
    keliling= d2*phi;
    jarak= (keliling*(counter/pulse));
    Serial.println(jarak);
  }
}
