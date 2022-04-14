
#define BLYNK_PRINT Serial
//Include Lib for Arduino to Nodemcu
#include <SoftwareSerial.h>
#include <ArduinoJson.h>

//D6 = Rx & D5 = Tx
SoftwareSerial nodemcu(D6, D5);

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


String readString;
String str1 = "";
String str2 = "";
String str3 = "";

char auth[] = "GlHW0YVgiBQyC0xVB8u0S1o0YsVFq5-O";  // blynk server
//blynk.coderscreed.in      C-oHpw9NmXinHTBNmD-gdFdp6yiciukF";
//RNY6ogiUBl8l_QKlZIu9ef367z4wXfK_



// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Android";
char pass[] = "Supersaiyan";



void setup() {
  // Initialize Serial port
   
  Serial.begin(9600);
   Blynk.begin(auth, ssid, pass); //"blynk.coderscreed.in", 8080);
  nodemcu.begin(9600);

 //while (!Serial) continue;
}

void loop() {
while(1){
   Blynk.run();
   
  StaticJsonDocument<1000> doc;
  DeserializationError error = deserializeJson(doc, nodemcu);

//   Test parsing
  if (error) {
    Serial.println("Invalid JSON Object");
 
    DeserializationError error = deserializeJson(doc, nodemcu);
  }

  Serial.println("JSON Object Recieved");
  Serial.print("Recieved Humidity:  ");
  String hum = doc["humidity"];
  Serial.println(hum);

  Serial.print("Recieved Temperature:  ");
  String temp = doc["temperature"];
  Serial.println(temp);

  Serial.print("Recieved Smoke:  ");
  String smoke = doc["smoke"];
  Serial.println(smoke);

  
  Serial.print("Recieved ECG:  ");
  String pulse = doc["pulse"];
  Serial.println(pulse);

  Serial.print("Recieved ECG:  ");
  String spo2 = doc["spo2"];
  Serial.println(spo2);

  Serial.print("Recieved ECG:  ");
  String ecg = doc["ecg"];
  Serial.println(ecg);
  
  Serial.println("-----------------------------------------");
//
    Blynk.virtualWrite(V2, hum);
    Blynk.virtualWrite(V1, temp);
    Blynk.virtualWrite(V3, smoke);
    Blynk.virtualWrite(V4, pulse);
    Blynk.virtualWrite(V5, spo2);
    Blynk.virtualWrite(V6, ecg);
//     
   delay(1);
}
}
 
