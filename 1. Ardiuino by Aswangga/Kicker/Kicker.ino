bool kick = 0;
int charge =250;
int kicker = 4,charger=5;//interface pada arduino

 
void setup()
{
  pinMode(kicker, OUTPUT);//charging capacitor
  pinMode(charger, OUTPUT);//kicker
  Serial.begin(9600);
  
}

void loop()
{

//  jika mode oper charge sampai 250
  bool kick = 0;
  char charge = 250;
  digitalWrite(charger,0);
  digitalWrite(kicker,0);

  
  //oper
    digitalWrite(charger,1);
    delay(2000);
    digitalWrite(charger,0);
    digitalWrite(kicker,1);
    delay(1000);
    digitalWrite(kicker,0);  
    delay(5000);

}++
