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
volatile long counter_y = 0;
volatile long counter_x = 0;
int lastCounter_x = 0;
int lastCounter_y = 0;
const int resolusi = 400;
float degrees_y;
float degrees_x;
float jarak_y = 0;
float jarak_x = 0;
float last_jarak_y;
float last_jarak_x;
float reset_jarak;
float last_jarak=0;
float arah_robot = 0;
float last_arah = 0, last_robot;
float error_arah = 0;
float arah_robot_koreksi;
float x;
float y;
float last_y = 0;
float last_x = 0;
float koordinat_y = 0;
float koordinat_x = 0;

float old_last_y = 0;
float old_last_x = 0;

float temp_x, temp_y;

// Kicker 

void baca_kick_data( const std_msgs::UInt8& kick_data) {
  kick = int(kick_data.data);
  if (kick == 10) { //charging
    digitalWrite(32, HIGH);
    delay(500);
  }  
  if (kick == 5) { //stop charging
    digitalWrite(32, LOW);
    delay(500);
    // digitalWrite(32, HIGH);
    // delay(50);
    digitalWrite(30, LOW);
    delay(200);
  }
  if (kick == 20) { //kick trigger kuat
    digitalWrite(32, LOW);
    delay(500);
    digitalWrite(30, HIGH);
    delay(100);
    digitalWrite(30, LOW);
    delay(200);

  }

}

ros::Subscriber<std_msgs::UInt8> sub("topic_kick", & baca_kick_data);

void setup() {
//  Pin Kicker

  pinMode(30, OUTPUT);
  pinMode(32, OUTPUT);
  
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

  counter_y;
 
//  ========================= BNO 055 =================================
  // Baca data orientasi dari sensor BNO055
  sensors_event_t event;
  bno.getEvent(&event);
  arah_robot = event.orientation.x ;//+ 90.0;

//  if (arah_robot > 360.0) {
//    arah_robot -= 360.0;
//  } else if (arah_robot < 0.0) {
//    arah_robot += 360.0;
//  }
  error_arah = last_arah - arah_robot;
//  arah_robot_koreksi = last_arah;

// ================= VECTOR ==================

  if (arah_robot - last_arah >= 10 || arah_robot - last_arah <= -10) {
      // Tampilkan nilai orientasi hanya jika perubahannya melebihi +/- 5 derajat
     
      // Perbarui nilai roll sebelumnya
      last_arah = arah_robot;
    }

    sudut.data = last_arah;

// ======================= BATAS VECTOR ==========================


 
 
//  ===============================================================================
// ================ MENGHITUNG KELILING LINGKARAN BERDASARKAN SUDUT ==================
 

//if (counter_y == lastCounter_y){
//
//  counter_y = 0;
////    lastCounter_y =0;
////    lastCounter_x =0;
//    
//}

////  ================ MENGECEK APAKAH BELOK =============================

  if (last_arah != arah_robot && (error_arah <= 5 || error_arah >= -5) || (lastCounter_y == counter_y)){


  counter_y = 0;
  lastCounter_y = 0;
  lastCounter_x = 0;
//  degrees_y = 360.0 * (lastCounter_y / (float)resolusi);
//  jarak_y = 0;
//  degrees_x = 360.0 * (lastCounter_x / (float)resolusi);
//  jarak_x = 0;

 
 
  }

  jarak_x = 0;
  jarak_y = 0;
  degrees_y = 360.0 * (lastCounter_y / (float)resolusi);
  jarak_y = 3.14 * 5.8 * (degrees_y / 360) ;//*  cos(last_arah * PI / 180);;
  degrees_x = 360.0 * (lastCounter_y / (float)resolusi);
  jarak_x = 3.14 * 5.8 * (degrees_x / 360) ;//* cos(last_arah * PI / 180);;
//  y = jarak_y * sin(last_arah* PI/180);
//  x = jarak_x * cos(last_arah * PI / 180);

    y = jarak_y * cos(last_arah* PI/180) ;
    x = jarak_x * sin(last_arah * PI / 180) ;
 
//  if(( degrees_y != 0 || degrees_x != 0)){
//    
//    
//    last_y = y;
//    last_x = x;
//  }

  float tempSebelumDItambah, nilai_y;
  if ((y != 0 && x != 0 ) ){

 
  tempSebelumDItambah = last_y;
  nilai_y = y;
  last_y = temp_y + y ;
  last_x = temp_x + x ;
  float nilaiLast_y = last_y;
  }
  if (lastCounter_y == counter_y){
  temp_y = last_y;
  temp_x = last_x;
  }

  Serial.print("nilai temp sebelum ditambah : ");
  Serial.println(tempSebelumDItambah);
  Serial.print("nilai y : ");
  Serial.println(nilai_y);
  Serial.print(" cm_y : ");
  Serial.println(last_y);
  Serial.print(" cm_x : ");
  Serial.println(last_x);


//  Serial.println("ini di eksekusi");
//  Serial.print(last_y);
//  Serial.println(" cm_y");

//  Serial.print(counter_x);
//  Serial.println(" pulse_x");
//  Serial.print(degrees_x);
//  Serial.println(" derajat_x");
//  Serial.print(last_x);
//  Serial.println(" cm_x");
//  }

//  =================== MENAMPILKAN KOORDINAT =======================

//if (last_robot != last_arah){
// Tampilkan nilai arah di Serial Monitor
  Serial.print("Arah (dalam derajat): ");
  Serial.println(last_arah);
//}
 
//    Serial.print(counter_y);
//Serial.print(lastCounter_y);
//  Serial.println(" pulse_y");
//  Serial.print(jarak_y);
//  Serial.println(" jarak y");
 

//
//  if(counter_y == 0){
//
//    temp_y = 0;
//    temp_x = 0;
//
//    temp_y = last_y;
//    temp_x = last_x;
//    
//  }
//
//    last_y = 0;
//    last_x = 0;
 
//  =============================================================
////  ================ MENGECEK APAKAH BELOK =============================
//
//  if (last_arah == arah_robot && (error_arah <= 5 || error_arah >= -5 ) && (lastCounter_y <= 1 || lastCounter_y >= -1)){
//
//    
////    lastCounter_y = lastCounter_y;
////    lastCounter_x = lastCounter_x;
//    counter_y = 0;
//    
//    
//    
//  }else{
//
//    lastCounter_y = counter_y;
//    lastCounter_x = counter_y;
//    
//  }
 
  lastCounter_y = counter_y;
//  counter_y = lastCounter_y;
  counter_x = counter_y;

//  
//  Serial.println("==========");
//  Serial.print(counter_y);
//  Serial.println("==========");
//  Serial.print(counter_x);
//  Serial.println("==========");
 
//   ====================================================================

// Data Terakhir
//  last_arah = arah_robot;

  last_robot = last_arah;



  // Terbitkan data ke ROS
  hasil.x = last_x;
  hasil.y = last_y;
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
