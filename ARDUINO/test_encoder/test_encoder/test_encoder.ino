float jarak1, jarak2, d1 = 10, keliling=0, pulse = 200, d2 = 5.8000;
const float phi = 3.142857142857143;
int temp, counter = 0; //This variable will increase or decrease depending on the rotation of encoder1
int temp2, counter2 = 0; //This variable will increase or decrease depending on the rotation of encoder1


void ai0() {
  // ai0 is activated if DigitalPin nr 2 is going from LOW to HIGH
  // Check pin 3 to determine the direction
  if(digitalRead(18)==LOW) {
  counter2--;
  }else{
  counter2++;
  }
}
   
void ai1() {
  // ai0 is activated if DigitalPin nr 3 is going from LOW to HIGH
  // Check with pin 2 to determine the direction
  if(digitalRead(2)==LOW) {
  counter--;
  }else{
  counter++;
  }
}

void setup() {
  pinMode(2, INPUT_PULLUP); // internal pullup input pin 2 
  pinMode(3, INPUT_PULLUP); // internal pullup input pin 3

  pinMode(18, INPUT_PULLUP); // internal pullup input pin 20 
  pinMode(19, INPUT_PULLUP); // internal pullup input pin 21  
  
  attachInterrupt(1, ai1, RISING);
  attachInterrupt(4, ai0, RISING);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if( counter != temp ){
    
    temp = counter;
    keliling = d1*phi ;
    jarak1 = ((keliling*(counter/pulse)));
  }

  if( counter2 != temp2 ){
    
    temp2 = counter2;
    keliling = d2*phi ;
    jarak2 = ((keliling*(counter2/pulse)));
  }
  Serial.print("jarak x :");
  Serial.println(jarak1);
  Serial.print("jarak y : ");
  Serial.println(jarak2);
  
  
}
