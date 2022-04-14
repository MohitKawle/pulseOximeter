                                                                             //Arduino side code
                                                                                  //DHT11 Lib
#include <DHT.h>

#define OLED_ADDR  0x3C
#define COUNTDOWN_TIME  15000ul                                                 // set timer for 15 sec

char
    szString[20];
byte
    mins, secs;
        
unsigned long
    timeTemp,
    timeNow,
    timeStart,
    timeElapsed,
    timeLeft;    
    
                                                                              //Arduino to NodeMCU Lib ( communication )
#include <SoftwareSerial.h>
#include <ArduinoJson.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128                                                  //--> OLED display width, in pixels
#define SCREEN_HEIGHT 64                                                  //--> OLED display height, in pixels

#define OLED_RESET  -1                                                    // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

                                                                        //Initialise Arduino to NodeMCU (5=Rx & 6=Tx)
SoftwareSerial nodemcu(5, 6);

                                                                          //Initialisation of DHT11 Sensor
#define DHTPIN 8
DHT dht(DHTPIN, DHT11);
float temp;
float hum;
int smoke;
int ecg;
int pulse,spo2;

#define SMOKEPIN A0
#define ECGPIN   A1

void setup() {
  Serial.begin(9600);
  pinMode(SMOKEPIN,INPUT);
  pinMode(10, INPUT);                                                    // Setup for leads off detection LO +
  pinMode(11, INPUT);                                                    // Setup for leads off detection LO -
  dht.begin();
  nodemcu.begin(9600);
  delay(1000);

  Serial.println("Program started");
   
   timeStart = millis();
    mins = 1;
    secs = 1;

   if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
     Serial.println(F("SSD1306 allocation failed"));
      for(;;); //--> Don't proceed, loop forever
  }
  display.display();
  delay(1000);
  display.clearDisplay();                                              //--> for Clearing the display

}



void tempe() 
{                                            // display values on oled (temp, humidity)
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10, 0); //--> (x position, y position)
  display.println("Temp:    Humidity: ");
  display.setCursor(10, 30); //--> (x position, y position)
  display.println(temp);
  display.setCursor(64, 30); //--> (x position, y position)
  display.println(hum);
  display.display();  
  //delay(10);
}


void smok() 
{                                          // display values on oled (smoke)
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10, 0); //--> (x position, y position)
  display.println("Air Quality:");
  display.setCursor(10, 30); //--> (x position, y position)
  display.println(smoke);
  display.display();  
  //delay(10);
}
 
void oxy() 
{                                       // display values on oled (pulse,spo2)
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10, 0); //--> (x position, y position)
  display.println("Pulse:    Spo2: ");
  display.setCursor(10, 30); //--> (x position, y position)
  display.println(pulse);
  display.setCursor(64, 30); //--> (x position, y position)
  display.println(spo2);
  display.display();  
  //delay(10);
}


void loop() {

   hum = dht.readHumidity();
  temp = dht.readTemperature(true);
  
   smoke = analogRead(SMOKEPIN);                                    // smoke reading start

   if((digitalRead(10) == 1)||(digitalRead(11) == 1)){              // ecg reading start
    Serial.println('!');
  }
  else{
                                                                  // send the value of analog input 0:
      ecg = analogRead(ECGPIN);
      Serial.println(analogRead(ECGPIN));
  }
                                                                //Wait for a bit to keep serial data from saturating
  delay(1);
          
  
  StaticJsonDocument<1000> doc;

                                                //Assign collected data to JSON Object
  doc["humidity"] = hum;                                    
  doc["temperature"] = temp;
  doc["smoke"] = smoke;
  doc["pulse"] = pulse;
  doc["spo2"] = spo2;
  doc["ecg"] = ecg;
  //Send data to NodeMCU
  serializeJson(doc, nodemcu);
  delay(1000);
 
}
  

void DoCountdown()                                          // timer/counter used for oled display purpose
{
       
    static unsigned long
        lastTimeNow = 0;
    static byte
        lastsecs = 1;

    timeNow = millis();
    timeElapsed = timeNow - timeStart;
    
        
    timeLeft = COUNTDOWN_TIME - timeElapsed;

    mins = (byte)(timeLeft / 60000ul);
    timeTemp = timeLeft - (mins * 60000);
    secs = (byte)(timeTemp / 1000ul);
    timeTemp = timeTemp - (secs * 1000ul);

    Serial.print(szString);
     if( mins == 0 && secs == 0 )                                     // if time left = 0 then reset timer go to loop() 
    {
        display.clearDisplay();
        timeStart = millis();
        mins = 1;
        secs = 1;
        return;
        
    }//if
    else if( secs != lastsecs )                                       // else continue loop
    { 
        display.clearDisplay();
        lastsecs = secs;
       
        if (timeLeft >= 10000ul) {                                              //if remaining time > 10000 print temp & humidity values on oled 
              tempe();
            } 
        else if(timeLeft >= 5000ul)                                             //if remaining time > 5000 print smoke value on oled 
          {
              smok();
          }
         else                                                                   //else print pulse and oxygen level on oled          {
              oxy();
          }
    
    }



void dht11_func() {                                     // reading dht11 values

  hum = dht.readHumidity();
  temp = dht.readTemperature(true);
//  Serial.print("Humidity: ");
//  Serial.println(hum);
//  Serial.print("Temperature: ");
//  Serial.println(temp);
//  Serial.print("Smoke: ");
//  Serial.println(smoke);
}
