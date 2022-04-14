// include the library code:
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//----------------------------------------

//----------------------------------------
#define SCREEN_WIDTH 128 //--> OLED display width, in pixels
#define SCREEN_HEIGHT 64 //--> OLED display height, in pixels
//----------------------------------------

//----------------------------------------Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
//----------------------------------------

#include "DHT.h"

// set the DHT Pin
#define DHTPIN 8



#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // set up the LCD's number of columns and rows: 
 Serial.begin(9600);

  //----------------------------------------SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  // Address 0x3C for 128x32 and Address 0x3D for 128x64.
  // But on my 128x64 module the 0x3D address doesn't work. What works is the 0x3C address.
  // So please try which address works on your module.
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); //--> Don't proceed, loop for
  }
      display.display();
  delay(1000);
  
  dht.begin();
  
  // Print a message to the LCD.
   display.clearDisplay(); //--> for Clearing the display
  //----------------------------------------Display text with text size 1
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10, 0); //--> (x position, y position)
  display.println("Temp:    Humidity: ");
  display.display(); 
  delay(2000);
}

void loop() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10, 0); //--> (x position, y position)
  display.println("Temp:    Humidity: ");
  display.display(); 
  delay(500);
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
     // read humidity
  float h = dht.readHumidity();
  //read temperature in Fahrenheit
  float f = dht.readTemperature(true);
   Serial.println(f);
  if (isnan(h) || isnan(f)) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(10, 0);
    
    display.println("ERROR ");
    display.display();
    return;
  }
  //display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10, 30); //--> (x position, y position)
  display.println(f);
  display.display(); 
  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(64, 30); //--> (x position, y position)
  display.println(h);
  display.display();  

  delay(1000);
}
