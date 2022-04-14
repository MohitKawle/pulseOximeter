
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

const int pSensor = A0;
int inputValue = 0;

void setup() {

  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  
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
  display.display();
  delay(1000);
  display.clearDisplay(); //--> for Clearing the display
}
// the loop function runs over and over again forever
void loop() {
  inputValue = analogRead (pSensor); // Analog Values 0 to 1023
  Serial.println (inputValue);
  analogWrite(LED_BUILTIN, inputValue/4);      // Mapping 0 to 255
  delay(1000);                     // Wait for two seconds (to demonstrate the active low LED)

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(50, 0); //--> (x position, y position)
  display.println(inputValue);
  display.display(); 
  delay(500);
  display.clearDisplay(); 
  }
