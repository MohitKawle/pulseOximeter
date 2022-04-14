/*
#include<SoftwareSerial.h>

#include "DHT.h"

// set the DHT Pin
#define DHTPIN 8



#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

SoftwareSerial nodemcu(2,3); 
 
int vresistor = A0; // variable resistor is connected with analog pin A0 of the Arduno
int vdatat = 0; 
int vdatah = 0;
String mystring; 
void setup()
{
 Serial.begin(9600); 
nodemcu.begin(9600); 
  dht.begin();

pinMode(vresistor, INPUT); 
}
 
void loop()
{
  float h = dht.readHumidity();
  float f = dht.readTemperature(true);
  //Serial.println(f);
  //Serial.println(h);
  delay(300);
 //vdata = analogRead(vresistor);  
  vdatat = f;
  vdatah = h;
  if (nodemcu.available() > 0 )
  {
  char data; 
  data = nodemcu.read(); 
  //Serial.println(data); 
  }
  mystring = mystring + vdatat;
  
  Serial.println(mystring); 

 nodemcu.println(mystring);
 
 //Serial.println(mystring1);  
//Serial.println(mystring2); 
 mystring = ""; 

delay(1000); 
}

*/


 /*
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
SoftwareSerial s(2,3);
#include "DHT.h"
#define DHTPIN 8     
#define DHTTYPE DHT11   
DHT dht(DHTPIN, DHTTYPE);
 
void setup() {
  Serial.begin(9600);
  s.begin(9600);
  pinMode(A0,INPUT);
  dht.begin();
  Serial.print("Hi");
}
    StaticJsonDocument<1000> jsonBuffer;

    DeserializationError error = deserializeJson(jsonBuffer ,s);
void loop() {
 
  float h = dht.readHumidity();
  
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);
 Serial.println(f);
 delay(100);
//  // Compute heat index in Fahrenheit (the default)
//  float hif = dht.computeHeatIndex(f, h);
//  // Compute heat index in Celsius (isFahreheit = false)
//  float hic = dht.computeHeatIndex(t, h, false);
//if (isnan(h) || isnan(t) || isnan(f)) {
//    return;
//  }
  // If the DHT-11 is not connected to correct pin or if it doesnot
//work no data will be sent
  //jsonBuffer["temp"] = f;
//  root["hum"] = h;
//  root["hi"] = hic;
//  root["gasv"]= analogRead(A0);
// 
//if(s.available()>0)
//{
// //jsonBuffer.printTo(s);
// serializeJson(jsonBuffer, s);
//}
}


*/

//Serial.print("H: ");
//Serial.print(h);
//Serial.print("% ");
//Serial.print(" T: ");
//Serial.print(t);
//Serial.println("C");
//str =String("coming from arduino: ")+String("H= ")+String(h)+String("T= ")+String(t);



#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 //--> OLED display width, in pixels
#define SCREEN_HEIGHT 64 //--> OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#include "DHT.h"
#include <SoftwareSerial.h>
#define DHTPIN 8
// Uncomment whatever type you're using!
//#define DHTTYPE DHT11 // DHT 11
#define DHTTYPE DHT11 
SoftwareSerial espSerial(2, 3);
DHT dht(DHTPIN, DHTTYPE);
String str;

void setup(){
  
Serial.begin(115200);
espSerial.begin(115200);
dht.begin();
 if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); //--> Don't proceed, loop forever
  }
   display.display();
delay(1000);
display.clearDisplay(); //--> for Clearing the display
}

void lcd(int tem, int hum){
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10, 0); //--> (x position, y position)
  display.println("Temp:    Humidity: ");
  display.setCursor(10, 30); //--> (x position, y position)
  display.println(tem);
  display.setCursor(64, 30); //--> (x position, y position)
  display.println(hum);
  display.display();  
  //delay(10);
  

  }

void loop()
{
 
  float h = dht.readHumidity();
// Read temperature 
  float t = dht.readTemperature(true);
  lcd(t,h);
  
  str = String(String(t) + String(h));
         Serial.println(str);

  espSerial.println(str);

}
