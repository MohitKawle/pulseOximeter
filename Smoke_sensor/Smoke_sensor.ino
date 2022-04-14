/*******

The MQ-2 smoke sensor is sensitive to smoke and to the following flammable gases:

LPG
Butane
Propane
Methane
Alcohol
Hydrogen

 All the resources for this project:
 https://www.hackster.io/Aritro

*******/

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

int redLed = 12;
int greenLed = 11;
int buzzer = 10;
int smokeA0 = A5;
// Your threshold value
int sensorThres = 400;

void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(smokeA0, INPUT);
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

  // Print a message to the LCD.
   display.clearDisplay(); //--> for Clearing the display
  //----------------------------------------Display text with text size 1
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10, 0); //--> (x position, y position)
  display.println("Air Quality: ");
  display.display(); 
  
  
}

void loop() {
  display.clearDisplay();
  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10, 0); //--> (x position, y position)
  display.println("Air Quality: ");
  display.display(); 
  int analogSensor = analogRead(smokeA0);

  Serial.print("Pin A0: ");
  Serial.println(analogSensor);

  //display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10, 10); //--> (x position, y position)
  display.println("Amount:");
  display.display(); 

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(60, 10); //--> (x position, y position)
  display.println(analogSensor);
  display.display(); 
  delay(500);
  
  // Checks if it has reached the threshold value
  if (analogSensor > sensorThres)
  {
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
    tone(buzzer, 1000, 200);
  }
  else
  {
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH);
    noTone(buzzer);
  }
  delay(100);


  
}
