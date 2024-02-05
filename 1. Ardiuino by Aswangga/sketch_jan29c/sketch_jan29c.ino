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
// Definisikan pin untuk rotary encoder
const int pin_yA = 2;
const int pin_yB = 3;

const int pin_xA = 18;
const int pin_xB = 19;

// Variabel untuk menyimpan status sebelumnya
volatile int lastState_yA;
volatile int lastState_yB;

volatile int lastState_xA;
volatile int lastState_xB;

volatile long counter_y = 0;
volatile long counter_x = 0;
const int resolusi = 400;
float degrees_y;
float degrees_x;
float hitung_y;
float hitung_x;

float test;

int muter = 0;


float x;
float y;

void setup() {
  // Set pin sebagai input
  pinMode(pin_yA, INPUT);
  pinMode(pin_yB, INPUT);

  // Aktifkan pull-up resistor internal
  digitalWrite(pin_yA, HIGH);
  digitalWrite(pin_yB, HIGH);

  // Atur interupsi untuk pin_yA
  attachInterrupt(digitalPinToInterrupt(pin_yA), updateCounter_y, CHANGE);

  attachInterrupt(digitalPinToInterrupt(pin_xA), updateCounter_x, CHANGE);

  // Inisialisasi status sebelumnya
  lastState_yA = digitalRead(pin_yA);
  lastState_yB = digitalRead(pin_yB);

  lastState_xA = digitalRead(pin_xA);
  lastState_xB = digitalRead(pin_xB);

  // Mulai serial monitor
  Serial.begin(9600);

  
}

void loop() {

}
  // Tampilkan nilai counter di serial monitor
//  Serial.println(counter);
  degrees_y = 360.0 * (counter_y / (float)resolusi);
  hitung_y = 3.14 * 5.8 * (degrees_y / 360);

  degrees_x = 360.0 * (counter_x / (float)resolusi);
  hitung_x = 3.14 * 10 * (degrees_x / 360);




//  Deteksi_belok(hitung_x);
  
  
//  Serial.print(counter_y);
//  Serial.println(" pulse_y");
//  Serial.print(degrees_y);
//  Serial.println(" derajat_y");
//  Serial.print(hitung_y);
//  Serial.println(" cm_y");

//  Serial.print(counter_x);
//  Serial.println(" pulse_x");
//  Serial.print(degrees_x);
//  Serial.println(" derajat_x");
//  Serial.print(hitung_x);
//  Serial.println(" cm_x");

  // Tunda sejenak untuk menghindari pembacaan berulang
  delay(500);

//  perpindahan_y(hitung);
}

void updateCounter_y() {
  int currentState_yA = digitalRead(pin_yA);
  int currentState_yB = digitalRead(pin_yB);

  int currentState_xA = digitalRead(pin_xA);
  int currentState_xB = digitalRead(pin_xB);

  // Deteksi perubahan

     if (currentState_yA != lastState_yA || currentState_yB != lastState_yB) {
      if (currentState_yA == currentState_yB) {
        counter_y++;
      } else {
        counter_y--;
      }
    }
      
    

  // Simpan status terakhir
    lastState_yA = currentState_yA;
    lastState_yB = currentState_yB;

}

void updateCounter_x() {
  int currentState_xA = digitalRead(pin_xA);
  int currentState_xB = digitalRead(pin_xB);
  
  // Deteksi perubahan
 
    if (currentState_xA != lastState_xA || currentState_xB != lastState_xB) {
      if (currentState_xA == currentState_xB) {
        counter_x++;
      } else {
        counter_x--;
      }
    }

  // Simpan status terakhir
  lastState_xA = currentState_xA;
  lastState_xB = currentState_xB;
}

//void perpindahan_y(float hitung){
//
//  int currentStateA = digitalRead(pinA);
//  int currentStateB = digitalRead(pinB);
//
//  float temp;
//  // Deteksi perubahan
//  if (currentStateA != lastStateA || currentStateB != lastStateB) {
//    if (currentStateA == currentStateB) {
//      temp = hitung;
//      hitung = temp + hitung;
//      y = hitung;
//    } else {
//      temp = hitung;
//      hitung = temp + (hitung * (-1));
//      y = hitung;
//    }
//  }
//
//  
//  
//
//  Serial.println(y);
//  delay(500);
//  
//}

void Deteksi_belok(int x){

  int currentState_yA = digitalRead(pin_yA);
  int currentState_yB = digitalRead(pin_yB);

  int currentState_xA = digitalRead(pin_xA);
  int currentState_xB = digitalRead(pin_xB);

// Deteksi Belok
//
//if((digitalRead(pin_xA) != lastState_xA && digitalRead(pin_xB) == lastState_xB) ||
//      (digitalRead(pin_xA) == lastState_xA && digitalRead(pin_xB) != lastState_xB) ||
//      (digitalRead(pin_yA) != lastState_yA && digitalRead(pin_yB) == lastState_yB) ||
//      (digitalRead(pin_yA) == lastState_yA && digitalRead(pin_yB) != lastState_yB)){
//
//  test = 360 * (x/(2*3.14*24));
//  muter = 1;
//  }else{
//  muter = 0;
//  }
//
//  Serial.print("Nilai Muter : ");
//  Serial.print(muter);
//  Serial.println("------------");
//
//
//  lastState_yA = currentState_yA;
//  lastState_yB = currentState_yB;
//  lastState_xA = currentState_xA;
//  lastState_xB = currentState_xB;
//  
//}
//








  Serial.begin(9600);
}

void loop() {
  int output = 0;

  if ((digitalRead(pinAX) != lastStateAX && digitalRead(pinBX) == lastStateBX) ||
      (digitalRead(pinAX) == lastStateAX && digitalRead(pinBX) != lastStateBX) ||
      (digitalRead(pinAY) != lastStateAY && digitalRead(pinBY) == lastStateBY) ||
      (digitalRead(pinAY) == lastStateAY && digitalRead(pinBY) != lastStateBY)) {
    output = 1;
  }

  Serial.println(output);

  lastStateAX = digitalRead(pinAX);
  lastStateBX = digitalRead(pinBX);
  lastStateAY = digitalRead(pinAY);
  lastStateBY = digitalRead(pinBY);

  delay(100);
}
