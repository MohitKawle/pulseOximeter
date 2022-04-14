// To install Boards and Libraries from NodeMCU ESP8266 on Arduino IDE see this video : https://www.youtube.com/watch?v=8jMr94B8iN0
// pin sclk - D1 [NODE MCU]
// pin sda - D2 [NODE MCU]
// pin sclk - Upper [UNO]
  // pin sda - lower [UNO]
//----------------------------------------Include Library
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

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  //----------------------------------------SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  // Address 0x3C for 128x32 and Address 0x3D for 128x64.
  // But on my 128x64 module the 0x3D address doesn't work. What works is the 0x3C address.
  // So please try which address works on your module.
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); //--> Don't proceed, loop forever
  }
  //----------------------------------------
  
  //----------------------------------------Show initial display buffer contents on the screen
  // the library initializes this with an Adafruit splash screen.
  // Show the display buffer on the screen(Update screen). You MUST call display() after
  // drawing commands to make them visible on screen!
  display.display();
  delay(1000);
  //----------------------------------------

  //____________________________________________________________________________________Display text & numbers
  display.clearDisplay(); //--> for Clearing the display
  //----------------------------------------Display text with text size 1
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10, 0); //--> (x position, y position)
  display.println("OLED");
  display.display(); 
  delay(2000);
  //----------------------------------------

  //----------------------------------------Display text with text size 2
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(10, 14); //--> (x position, y position)
  display.println("Hi");
  display.display(); 
  delay(2000);
  //----------------------------------------

  //----------------------------------------Displaying Inverted Text
  display.setTextSize(1);
  display.setTextColor(BLACK, WHITE); // 'inverted' text
  display.setCursor(10,35); //--> (x position, y position)
  display.println("Hrishikesh");
  display.display();
  delay(2000);
  //----------------------------------------

  //----------------------------------------Displaying Numbers
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10,50); //--> (x position, y position)
  display.println(1234567890);
  display.display();
  delay(2000);
 //----------------------------------------
  display.clearDisplay(); //--> for Clearing the display

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10,0); //--> (x position, y position)
  display.println("New Screen");
  display.display();
  delay(2000);
  //----------------------------------------
  //____________________________________________________________________________________

}

void loop() {
  
}
