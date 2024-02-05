#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

Adafruit_BNO055 bno = Adafruit_BNO055();
float previousRoll = 0.0; // Untuk menyimpan nilai roll sebelumnya

void setup(void)
{
  Serial.begin(9600);
  
  if (!bno.begin())
  {
    Serial.print("Tidak dapat menemukan sensor BNO055");
    while (1);
  }

  bno.setExtCrystalUse(true);
}

void loop(void)
{
  sensors_event_t event;
  bno.getEvent(&event);

  // Membaca nilai orientasi (roll, pitch, yaw)
  float roll = event.orientation.x + 90.0; // Menambahkan 90 derajat
  float pitch = event.orientation.y;
  float yaw = event.orientation.z;

  // Normalisasi nilai roll
  if (roll > 360.0) {
    roll -= 360.0;
  } else if (roll < 0.0) {
    roll += 360.0;
  }

  // Memeriksa perubahan roll sebesar +/- 5 derajat
  if (roll - previousRoll >= 5.0 || roll - previousRoll <= -5.0) {
    // Tampilkan nilai orientasi hanya jika perubahannya melebihi +/- 5 derajat
    Serial.print("Roll: ");
    Serial.print(roll);
    Serial.print(" Pitch: ");
    Serial.print(pitch);
    Serial.print(" Yaw: ");
    Serial.println(yaw);
    // Perbarui nilai roll sebelumnya
    previousRoll = roll;
  }

  delay(100);
}
