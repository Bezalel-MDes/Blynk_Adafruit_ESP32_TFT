/*************************************************************
  A test of Blynk API and TFT Display on ESP32 (Adafruit ESP32-S2 Reverse TFT Feather)

  Code generatted via: https://examples.blynk.cc
  And this example: https://learn.adafruit.com/esp32-s2-reverse-tft-feather/built-in-tft
  
  You can use this sketch as a debug tool that prints all incoming values
  sent by a widget connected to a Virtual Pin 1 in the Blynk App.

  App dashboard setup:
    Slider widget (0...100) on V1
 *************************************************************/

// TFT Display Modules
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>

// Use dedicated hardware SPI pins
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

// Blynk Config
/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID           "xxxx"
#define BLYNK_TEMPLATE_NAME         "xxxx"
#define BLYNK_AUTH_TOKEN            "xxxx"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

// Blynk and Network
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "xxxx";
char pass[] = "xxxx";

// DEfien built in LED
int led = LED_BUILTIN;

// This function will be called every time Slider Widget
// in Blynk app writes values to the Virtual Pin 1
BLYNK_WRITE(V1)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  // You can also use:
  // String i = param.asStr();
  // double d = param.asDouble();
  Serial.print("V1 Slider value is: ");
  Serial.println(pinValue);

  if(pinValue == 1){
    digitalWrite(led, HIGH);
    tft.fillScreen(ST77XX_GREEN);
    testdrawtext("ON!", ST77XX_BLACK);    
  } else {
    digitalWrite(led, LOW);
    tft.fillScreen(ST77XX_RED);
    testdrawtext("OFF!", ST77XX_WHITE);        
  }

}

void setup()
{

  Serial.begin(115200);
  pinMode(led, OUTPUT);

  Serial.print(F("Setting up Feather TFT Test"));
  pinMode(TFT_BACKLITE, OUTPUT);
  digitalWrite(TFT_BACKLITE, HIGH);
  pinMode(TFT_I2C_POWER, OUTPUT);
  digitalWrite(TFT_I2C_POWER, HIGH);
  delay(10);
  tft.init(135, 240); // Init ST7789 240x135
  tft.setRotation(3);
  tft.fillScreen(ST77XX_BLACK);
  Serial.println(F("TFT Initialized"));

  // INITIALIZE BLYNK 
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  // You can also specify server:
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);
}

void loop()
{
  Blynk.run();
}

void testdrawtext(char *text, uint16_t color) {
  tft.setCursor(10, 20);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.setTextSize(8);
  tft.print(text);
}