#include <ros.h>
#include <std_msgs/Float32.h>
#include <geometry_msgs/Point.h>
#include <Adafruit_BNO055.h>

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
volatile long counter_A = 0;
volatile long counter_B = 0;
int lastCounter_A = 0;

int lastCounter_B = 0;

const int resolusi = 400;
float degrees_yA;
float degrees_xA;
float degrees_B;

float jarak_yA = 0;
float jarak_xA = 0;
float jarak_yB = 0;
float jarak_xB = 0;

float last_jarak_y;
float last_jarak_x;
float reset_jarak;
float last_jarak=0;
float arah_robot = 0;
float last_arah = 0, last_robot;
float error_arah = 0;
float arah_robot_koreksi;

float xA;
float yA;
float xB;
float yB;

float last_yA = 0;
float last_xA = 0;
float last_yB = 0;
float last_xB = 0;

float koordinat_y = 0;
float koordinat_x = 0;

float old_last_y = 0;
float old_last_x = 0;

float temp_xA, temp_yA, temp_yB, temp_xB;

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

  counter_A;
  counter_B;
  
//  ========================= BNO 055 =================================
  // Baca data orientasi dari sensor BNO055
  sensors_event_t event;
  bno.getEvent(&event);
  arah_robot = event.orientation.x ;
  
  error_arah = last_arah - arah_robot;
  arah_robot_koreksi = last_arah;

// ================= VECTOR ==================

  if (arah_robot - last_arah >= 10 || arah_robot - last_arah <= -10) {
      // Tampilkan nilai orientasi hanya jika perubahannya melebihi +/- 5 derajat
      
      // Perbarui nilai roll sebelumnya
      last_arah = arah_robot;
    }

    sudut.data = last_arah;


  if (last_arah != arah_robot && (error_arah <= 5 || error_arah >= -5) || (lastCounter_A == counter_A && lastCounter_B == counter_B)){


    counter_A = 0;
    lastCounter_A = 0;
//    lastCounter_A = 0;
  
    counter_B = 0;
    lastCounter_B = 0;
  }

  jarak_xA = 0;
  jarak_yA = 0;
  jarak_xB = 0;
  jarak_yB = 0;
  
  degrees_yA = 360.0 * (lastCounter_A / (float)resolusi);
  jarak_yA = 3.14 * 5.8 * (degrees_yA / 360) ;//*  cos(last_arah * PI / 180);;
  degrees_xA = 360.0 * (lastCounter_A / (float)resolusi);
  jarak_xA = 3.14 * 5.8 * (degrees_xA / 360) ;//* cos(last_arah * PI / 180);;

  degrees_B = 360.0 * (lastCounter_B / (float)resolusi);
  jarak_yB = 3.14 * 10 * (degrees_B / 360) ;//*  cos(last_arah * PI / 180);;
  jarak_xB = 3.14 * 10 * (degrees_B/ 360) ;//* cos(last_arah * PI / 180);;



    yA = jarak_yA * cos(last_arah* PI/180) ;
    xA = jarak_xA * sin(last_arah * PI / 180) ;

    yB = jarak_yB * sin(last_arah * PI/180);
    xB = jarak_xB *cos(last_arah * PI/180); 
    
  float tempSebelumDItambah, nilai_yA;
  if ((yA != 0 && xA != 0 ) || (yB != 0 && xB != 0) ){
//    tempSebelumDItambah = last_yA;
//    nilai_yA = yA;
    last_yA = temp_yA + yA ;
    last_xA = temp_xA + xA ;

    last_yB = temp_yB + yB ;
    last_xB = temp_xB + xB ;
    
//    float nilaiLast_yA = last_yA;
  }
  if (lastCounter_A == counter_A || lastCounter_B == counter_B){
    temp_yA = last_yA;
    temp_xA = last_xA;

    temp_yB = last_yB;
    temp_xB = last_xB;
  }

  koordinat_y = last_yA + last_yB;
  koordinat_x = last_xA + last_xB;

  Serial.print("nilai temp sebelum ditambah : ");
  Serial.println(tempSebelumDItambah);
  Serial.print("nilai y : ");
  Serial.println(nilai_yA);
  Serial.print("nilai counter_B : ");
  Serial.println(counter_A);
  Serial.print(" cm_y : ");
  Serial.println(koordinat_y);
  Serial.print(" cm_x : ");
  Serial.println(koordinat_x);


//  =================== MENAMPILKAN KOORDINAT =======================

// Tampilkan nilai arah di Serial Monitor
  Serial.print("Arah (dalam derajat): ");
  Serial.println(last_arah);
  
  lastCounter_A = counter_A;
//  counter_xA = counter_yA;

  lastCounter_B = counter_B;

// Data Terakhir
  last_arah = arah_robot;

  last_robot = last_arah;



  // Terbitkan data ke ROS
  hasil.x = koordinat_x;
  hasil.y = koordinat_y;
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
  if ((currentState_yA != lastState_yA || currentState_yB != lastState_yB)) {
    if (currentState_yA == currentState_yB) {
      counter_A++;
    }
    else {
      counter_A--;
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
      counter_B++;
    }
    else {
      counter_B--;
    }
  }


  // Simpan status terakhir
  lastState_yA = currentState_yA;
  lastState_yB = currentState_yB;
  lastState_xA = currentState_xA;
  lastState_xB = currentState_xB;
}

float hitungKoordinat(float x, float y){
  float current_x, current_y, koreksi_x, koreksi_y;

if (current_y != y || current_x != x){
  koreksi_x = koreksi_y + x;
  koreksi_y = koreksi_x + y;
}
  current_x = x;
  current_y = y;

  return koreksi_x, koreksi_y;
  
}
