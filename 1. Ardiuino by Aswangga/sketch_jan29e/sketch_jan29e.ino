// Mendefinisikan pin untuk encoder 1
const int pin_clk_1 = 2;
const int pin_dt_1 = 3;

// Mendefinisikan pin untuk encoder 2
const int pin_clk_2 = 4;
const int pin_dt_2 = 5;

// Inisialisasi variabel counter
int counter = 0;
int last_counter_1 = 0;
int last_counter_2 = 0;

void setup() {
  // Mengatur pin sebagai input
  pinMode(pin_clk_1, INPUT);
  pinMode(pin_dt_1, INPUT);
  pinMode(pin_clk_2, INPUT);
  pinMode(pin_dt_2, INPUT);

  // Mengaktifkan pull-up resistor
  digitalWrite(pin_clk_1, HIGH);
  digitalWrite(pin_dt_1, HIGH);
  digitalWrite(pin_clk_2, HIGH);
  digitalWrite(pin_dt_2, HIGH);

  // Memulai serial communication
  Serial.begin(9600);

  // Attach interrupt untuk encoder 1
  attachInterrupt(digitalPinToInterrupt(pin_clk_1), updateCounter, CHANGE);

  // Attach interrupt untuk encoder 2
  attachInterrupt(digitalPinToInterrupt(pin_clk_2), updateCounter, CHANGE);
}

void loop() {
  // Tidak ada yang perlu dilakukan di loop utama
}

void updateCounter() {
  int clk_1 = digitalRead(pin_clk_1);
  int dt_1 = digitalRead(pin_dt_1);
  int clk_2 = digitalRead(pin_clk_2);
  int dt_2 = digitalRead(pin_dt_2);

  if ((clk_1 != dt_1) && (clk_2 != dt_2)) {
    return; // Keduanya berputar, keluar dari fungsi
  }

  if (digitalPinToInterrupt(pin_clk_1) == digitalPinToInterrupt(pin_clk_1)) {
    if (clk_1 != last_counter_1) {
      if (dt_1 != clk_1) {
        counter++;
      } else {
        counter--;
      }
    }
    last_counter_1 = clk_1;
  } else if (digitalPinToInterrupt(pin_clk_2) == digitalPinToInterrupt(pin_clk_2)) {
    if (clk_2 != last_counter_2) {
      if (dt_2 != clk_2) {
        counter++;
      } else {
        counter--;
      }
    }
    last_counter_2 = clk_2;
  }

  Serial.print("Counter: ");
  Serial.println(counter);
}
