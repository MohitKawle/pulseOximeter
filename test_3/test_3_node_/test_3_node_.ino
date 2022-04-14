
/*
#define BLYNK_PRINT Serial

#include <SoftwareSerial.h>
SoftwareSerial espSerial(2, 3);

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

String readString;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "RNY6ogiUBl8l_QKlZIu9ef367z4wXfK_";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Android";
char pass[] = "Supersaiyan";

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass, "coderscreed.in", 8080);
  while (!Serial) {
  ; // wait for serial port to connect. Needed for native USB port only
  }
}



void loop()
{

  Blynk.run();
  
while (Serial.available()) {
    delay(10);  
    if (Serial.available() >0) {
      char c = Serial.read();  //gets one byte from serial buffer
      readString += c; //makes the string readString
      Serial.print("Hi");
    } 
  }

     Blynk.run();
 
  if (readString.length() >0) {
      Serial.println(readString);      
      
      str1 = readString.substring(0, 5); //get the first five characters
      Serial.println(str1);  //print ot serial monitor to see results
      Blynk.virtualWrite(V1,str1);
          
      str2 = readString.substring(5, 10); //get the next five characters 
      Serial.println(str2);
      Blynk.virtualWrite(V2,str2);   
      
   
    readString = "";
  }
 
 }
  
*/

#define BLYNK_PRINT Serial

#include <SoftwareSerial.h>
SoftwareSerial espSerial(2, 3);

 #include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


String readString;
String str1 = "";
String str2 = "";

char auth[] = "RNY6ogiUBl8l_QKlZIu9ef367z4wXfK_";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Android";
char pass[] = "Supersaiyan";


void setup() {
  espSerial.begin(115200);
  Serial.begin(115200);
   Blynk.begin(auth, ssid, pass, "coderscreed.in", 8080);
 
}
 
void loop() {

  Blynk.run();

  while (Serial.available()) {
    delay(3);  
    char c = Serial.read();
    readString += c; 
  }

  if (readString.length() >0) {
    Serial.println(readString);

    str1 = readString.substring(0, 5); //get the first four characters
    str2 = readString.substring(5, 7); //get the next four characters 

    Serial.println(str1);
    Serial.println(str2);

    Blynk.virtualWrite(V1, str1);
    Blynk.virtualWrite(V2, str2);
     
    readString="";
  } 
}























































//
//  if (Serial.available()) {
//    Serial.write(Serial.read());
//   
//     char c = Serial.read();  //gets one byte from serial buffer
//     readString += c; //makes the string readString
//  }
//}     
//          Serial.println();
//          Serial.println(readString);
//            Blynk.run();
//if (readString.length() > 0) {

//                Serial.println(readString);

//      str1 = readString.substring(0, 5); //get the first five characters      
//      str2 = readString.substring(5, 7); //get the next five characters 
//      
//      Serial.println(str1);  //print ot serial monitor to see results
//      
//      Serial.println(str2);
//      
//      Blynk.virtualWrite(V1,str1);
//      Blynk.virtualWrite(V2,str2);   
      
   

//  }
//}

  
//  
//while (Serial.available()) {
//    delay(10);  
//   
//
//     
// 
//  
// }
 
 

  
/*
 
void setup() {
// Open serial communications and wait for port to open:
Serial.begin(115200);
while (!Serial) {
; // wait for serial port to connect. Needed for native USB port only
}
}
void loop() { // run over and over
if (Serial.available()) {
Serial.write(Serial.read());
}
*/
