#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "PxSilR86WLgm32DJ-L1Cs4dgDl84_iob";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Android";
char pass[] = "Supersaiyan";

WidgetLCD lcd(V1);

void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(D3,OUTPUT);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  lcd.clear(); //Use it to clear the LCD Widget
  lcd.print(4, 0, "Hello"); // use: (position X: 0-15, position Y: 0-1, "Message you want to print")
  lcd.print(4, 1, "World");
  // Please use timed events when LCD printintg in void loop to avoid sending too many commands
  // It will cause a FLOOD Error, and connection will be dropped
}

void loop()
{
  digitalWrite(D3,HIGH);
  Blynk.run();
}
