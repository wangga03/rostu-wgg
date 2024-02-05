#include <ros.h>
#include <std_msgs/Float32.h>
#include <geometry_msgs/Point.h>
#include <Adafruit_BNO055.h>
#include <math.h>

Adafruit_BNO055 bno = Adafruit_BNO055();

ros::NodeHandle koordinat;
std_msgs::Float32 sudut;
geometry_msgs::Point hasil;
ros::Publisher positioning_encoder("Diagram", &hasil);
ros::Publisher sudut_bno("sudut_bno", &sudut);

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
int lastCounter_y = 0;
int lastCounter_x = 0;
const int resolusi = 400;
float degrees_y;
float degrees_x;
float jarak_y = 0;
float jarak_x = 0;
float last_jarak_y = 0;
float last_jarak_x = 0;
float arah_robot = 0;
float last_arah = 0;

// Variabel untuk menyimpan jarak per pulsa dari encoder
float jarak_per_pulsa_x = 0.1; // Misalnya, jarak 0.1 cm per pulsa
float jarak_per_pulsa_y = 0.1; // Misalnya, jarak 0.1 cm per pulsa

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
  koordinat.advertise(positioning_encoder);
  koordinat.advertise(sudut_bno);

  // Mulai komunikasi serial
  Serial.begin(57600);

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
  arah_robot = event.orientation.x + 90.0;

  if (arah_robot > 360.0) {
    arah_robot -= 360.0;
  } else if (arah_robot < 0.0) {
    arah_robot += 360.0;
  }

  float delta_arah = arah_robot - last_arah;

  // Reset counter jika arah berubah
  if (fabs(delta_arah) > 5) { // Ubah angka 5 sesuai dengan ambang batas perubahan arah yang diinginkan
    counter_x = 0;
    counter_y = 0;
  }

  // Koreksi perubahan jarak berdasarkan perubahan counter
  float delta_jarak_x = counter_x * jarak_per_pulsa_x; // Sesuaikan dengan nilai jarak per pulsa
  float delta_jarak_y = counter_y * jarak_per_pulsa_y; // Sesuaikan dengan nilai jarak per pulsa

  // Hitung total jarak
  jarak_x += delta_jarak_x;
  jarak_y += delta_jarak_y;

  // Simpan nilai arah sebelumnya
  last_arah = arah_robot;

  // Tampilkan informasi di Serial Monitor
  Serial.println("Informasi:");
  Serial.print("Arah Robot: ");
  Serial.println(arah_robot);
  Serial.print("Jarak X: ");
  Serial.println(jarak_x);
  Serial.print("Jarak Y: ");
  Serial.println(jarak_y);

  // Terbitkan data ke ROS
  hasil.x = jarak_x;
  hasil.y = jarak_y;
  positioning_encoder.publish(&hasil);
  sudut_bno.publish(&sudut);

  // Tunda sejenak untuk menghindari pembacaan berulang
  delay(500);
}

void updateCounter_y() {
  int currentState_yA = digitalRead(pin_yA);
  int currentState_yB = digitalRead(pin_yB);
  int currentState_xA = digitalRead(pin_xA);
  int currentState_xB = digitalRead(pin_xB);

  // Deteksi perubahan
  if ((currentState_yA != lastState_yA || currentState_yB != lastState_yB) &&
      (currentState_xA == lastState_xA && currentState_xB == lastState_xB)) {
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
