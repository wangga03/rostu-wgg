const int pinAX = 2;
const int pinBX = 3;
const int pinAY = 18;
const int pinBY = 19;

volatile int lastStateAX;
volatile int lastStateBX;
volatile int lastStateAY;
volatile int lastStateBY;

volatile long counterX = 0;
volatile long counterY = 0;

void setup() {
  pinMode(pinAX, INPUT);
  pinMode(pinBX, INPUT);
  pinMode(pinAY, INPUT);
  pinMode(pinBY, INPUT);

  digitalWrite(pinAX, HIGH);
  digitalWrite(pinBX, HIGH);
  digitalWrite(pinAY, HIGH);
  digitalWrite(pinBY, HIGH);

  attachInterrupt(digitalPinToInterrupt(pinAX), updateCounterX, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pinAY), updateCounterY, CHANGE);

  lastStateAX = digitalRead(pinAX);
  lastStateBX = digitalRead(pinBX);
  lastStateAY = digitalRead(pinAY);
  lastStateBY = digitalRead(pinBY);

  Serial.begin(9600);
}

void loop() {
  Serial.print("Counter X: ");
  Serial.println(counterX);
  Serial.print("Counter Y: ");
  Serial.println(counterY);
  Serial.println("-------------");

  delay(2000);
}

void updateCounterX() {
  int currentStateAX = digitalRead(pinAX);
  int currentStateBX = digitalRead(pinBX);

  if (currentStateAX != lastStateAX || currentStateBX != lastStateBX) {
    if (currentStateAX == currentStateBX) {
      counterX++;
    } else {
      counterX--;
    }
  }

  lastStateAX = currentStateAX;
  lastStateBX = currentStateBX;
}

void updateCounterY() {
  int currentStateAY = digitalRead(pinAY);
  int currentStateBY = digitalRead(pinBY);

  if (currentStateAY != lastStateAY || currentStateBY != lastStateBY) {
    if (currentStateAY == currentStateBY) {
      counterY++;
    } else {
      counterY--;
    }
  }

  lastStateAY = currentStateAY;
  lastStateBY = currentStateBY;
}
