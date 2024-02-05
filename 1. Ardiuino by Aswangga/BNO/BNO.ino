#include <ros.h>
#include <std_msgs/Float32.h>
#include <Adafruit_BNO055.h>

Adafruit_BNO055 bno = Adafruit_BNO055();

ros::NodeHandle koordinat;
std_msgs::Float32 flt_msg_y;
std_msgs::Float32 flt_msg_x;
ros::Publisher positioning_y("position_y", &flt_msg_y);
ros::Publisher positioning_x("position_x", &flt_msg_x);

// Definisikan pin untuk rotary encoder
const int pin_yA = 2;
const int pin_yB = 3;

const int pin_xA = 19;
const int pin_xB = 18;

// Variabel untuk menyimpan status sebelumnya
volatile int lastState_yA;
volatile int lastState_yB;
volatile int lastState_xA;
volatile int lastState_xB;
volatile long counter_y = 0;
volatile long counter_x = 0;
int lastCounter_x = 0;
int lastCounter_y = 0;
const int resolusi = 400;
float degrees_y;
float degrees_x;
float hitung_y;
float hitung_x;
float arah_robot;
float last_arah = 0;
float x;
float y;

void setup() {
  // Set pin sebagai input
  pinMode(pin_yA, INPUT);
  pinMode(pin_yB, INPUT);
  pinMode(pin_xA, INPUT);
  pinMode(pin_xB, INPUT);

  // Aktifkan pull-up resistor internal
  digitalWrite(pin_yA, HIGH);
  digitalWrite(pin_yB, HIGH);
  digitalWrite(pin_xA, HIGH);
  digitalWrite(pin_xB, HIGH);

  // Atur interupsi untuk pin_yA
  attachInterrupt(digitalPinToInterrupt(pin_yA), updateCounter_y, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pin_xA), updateCounter_x, CHANGE);

  // Inisialisasi status sebelumnya
  lastState_yA = digitalRead(pin_yA);
  lastState_yB = digitalRead(pin_yB);
  lastState_xA = digitalRead(pin_xA);
  lastState_xB = digitalRead(pin_xB);

  // Inisialisasi node ROS dan publisher
  koordinat.initNode();
  koordinat.advertise(positioning_y);
  koordinat.advertise(positioning_x);

  // Mulai komunikasi serial
  Serial.begin(9600);

  // Inisialisasi sensor BNO055
  if (!bno.begin())
  {
    Serial.println("Could not find a valid BNO055 sensor, check wiring!");
    while (1);
  }
}

void loop() {
  // Baca data orientasi dari sensor BNO055
  sensors_event_t event;
  bno.getEvent(&event);
  arah_robot = event.orientation.x;

  // Tampilkan nilai arah di Serial Monitor
  Serial.print("Heading: ");
  Serial.println(arah_robot);

  // Tampilkan nilai counter di Serial Monitor
  degrees_y = 360.0 * (lastCounter_y / (float)resolusi);
  hitung_y = 3.14 * 5.8 * (degrees_y / 360);
  degrees_x = 360.0 * (lastCounter_x / (float)resolusi);
  hitung_x = 3.14 * 10 * (degrees_x / 360);

//    Serial.print(counter_y);
//  Serial.println(" pulse_y");
//  Serial.print(degrees_y);
//  Serial.println(" derajat_y");
  Serial.print(hitung_y);
  Serial.println(" cm_y");

//  Serial.print(counter_x);
//  Serial.println(" pulse_x");
//  Serial.print(degrees_x);
//  Serial.println(" derajat_x");
  Serial.print(hitung_x);
  Serial.println(" cm_x");

  if (last_arah == arah_robot){

    lastCounter_y = counter_y;
    lastCounter_x = counter_x;
    
  }else{

    lastCounter_y = lastCounter_y;
    lastCounter_x = lastCounter_x;
    
  }


  last_arah = arah_robot;

  // Terbitkan data ke ROS
  flt_msg_y.data = hitung_y;
  flt_msg_x.data = hitung_x;
  positioning_y.publish(&flt_msg_y);
  positioning_x.publish(&flt_msg_x);
  koordinat.spinOnce();

  // Tunda sejenak untuk menghindari pembacaan berulang
  delay(500);
}

void updateCounter_y() {
  int currentState_yA = digitalRead(pin_yA);
  int currentState_yB = digitalRead(pin_yB);
  int currentState_xA = digitalRead(pin_xA);
  int currentState_xB = digitalRead(pin_xB);

  // Deteksi perubahan
  if ((currentState_yA != lastState_yA || currentState_yB != lastState_yB)) {
    if (currentState_yA == currentState_yB) {
      counter_y++;
    }
    else {
      counter_y--;
    }
  }

  // Simpan status terakhir
  lastState_yA = currentState_yA;
  lastState_yB = currentState_yB;
  lastState_xA = currentState_xA;
  lastState_xB = currentState_xB;
}

void updateCounter_x() {
  int currentState_yA = digitalRead(pin_yA);
  int currentState_yB = digitalRead(pin_yB);
  int currentState_xA = digitalRead(pin_xA);
  int currentState_xB = digitalRead(pin_xB);

  // Deteksi perubahan
  if ((currentState_xA != lastState_xA || currentState_xB != lastState_xB)) {
    if (currentState_xA == currentState_xB) {
      counter_x++;
    }
    else {
      counter_x--;
    }
  }

  // Simpan status terakhir
  lastState_yA = currentState_yA;
  lastState_yB = currentState_yB;
  lastState_xA = currentState_xA;
  lastState_xB = currentState_xB;
}
