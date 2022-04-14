const int gasPin = A0; //GAS sensor output pin to Arduino analog A0 pin
const int buzpin = 9;

void setup()
{
  pinMode(buzpin,OUTPUT);
  Serial.begin(9600); //Initialize serial port - 9600 bps
}

void loop()
{
  Serial.println(analogRead(gasPin));
  if (gaspin >= 200){
      digitalWrite(buzpin,HIGH);
      
    }
  else{
     digitalWrite(buzpin,LOW);
    }
  delay(1000); // Print value every 1 sec.
}
