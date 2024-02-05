const int pinAX = 2;
const int pinBX = 3;
const int pinAY = 18;
const int pinBY = 19;

volatile int lastStateAX;
volatile int lastStateBX;
volatile int lastStateAY;
volatile int lastStateBY;

void setup() {
  pinMode(pinAX, INPUT);
  pinMode(pinBX, INPUT);
  pinMode(pinAY, INPUT);
  pinMode(pinBY, INPUT);

  digitalWrite(pinAX, HIGH);
  digitalWrite(pinBX, HIGH);
  digitalWrite(pinAY, HIGH);
  digitalWrite(pinBY, HIGH);

  lastStateAX = digitalRead(pinAX);
  lastStateBX = digitalRead(pinBX);
  lastStateAY = digitalRead(pinAY);
  lastStateBY = digitalRead(pinBY);

  Serial.begin(9600);
}

void loop() {
  int output = 0;

  if ((digitalRead(pinAX) != lastStateAX && digitalRead(pinBX) != lastStateBX) ||
      (digitalRead(pinAY) != lastStateAY && digitalRead(pinBY) != lastStateBY)) {
    output = 1;
  }else{
    output = 0;
  }

  Serial.println(output);

  lastStateAX = digitalRead(pinAX);
  lastStateBX = digitalRead(pinBX);
  lastStateAY = digitalRead(pinAY);
  lastStateBY = digitalRead(pinBY);

  delay(100);
}
