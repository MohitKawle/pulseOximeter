// for arduino uno

#include "DHT.h" //dht DHT; 

float h,f;

#define DHT11_PIN A0
String str;

#define DHTPIN 8
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);



void setup(){
 Serial.begin(115200);
 Serial.begin(115200);
 Serial.print(char(169)); // Copyright Symbol
 Serial.println(" Myengineeringstuffs.com");
 delay(2000);
}
void loop()
{
   // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
     // read humidity
  float h = dht.readHumidity();
  //read temperature in Fahrenheit
  float f = dht.readTemperature(true);
  Serial.print("H: ");
  Serial.print(h); 
  Serial.print("% ");
  Serial.print(" T: ");
  Serial.print(f); 
  Serial.print(char(176));
  Serial.println("C");
  str =String('H')+String(h)+String('T')+String(f);
  Serial.println(str);
  delay(5000);
}
