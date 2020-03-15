#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1331.h>
#include <SPI.h>
//#include <String.h>
//color definitions for OLED SPI screen SSD1331 
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

//define pins for items used
#define OLEDCS 10
#define OLEDDC 11
#define OLEDRES 8
#define OLEDSDA A4
#define OLEDSCL A5

//pin used for temp/humidity sensor
#define DHT11 2

//pin used for photocell
#define PHOTOCELL A7 

//pin used for soil moisture sensor
#define SOILMOISTURE A6

//pins used on the 3 color led
#define LEDGREEN 9
#define LEDRED 6
#define LEDBLUE 5

//create display
Adafruit_SSD1331 screen = Adafruit_SSD1331(OLEDCS, OLEDDC, OLEDSDA, OLEDSCL, OLEDRES);
/*
This function will print the headers 
on the screen
over the values over the values that
will be chaning, This text will not 
change and is meant to be ran only 
once.
*/
void setHeaders()
{
  screen.setCursor(0,0);
  screen.print("Temp");
  screen.setCursor(47,0);
  screen.print("Hum");
  screen.setCursor(0,33);
  screen.print("Soil");
  screen.setCursor(47, 33);
  screen.print("Message");
}
/*
This will redraw only the text under the 
headers (the values that are changing)
to the same color as the back ground so 
that only the area that needs to be updated
on the screen will be redrawn
*/
template <class T>
void clear(T colorBackground, T colorText, int eraseTemp, int eraseHum, int eraseSoil, char eraseMsg[])
{
  screen.setTextColor(colorBackground,colorBackground);
  screen.setCursor(0,45); //TEMP 
  screen.print(eraseTemp);
  screen.setCursor(0, 12); //HUM
  screen.print(eraseHum);
  screen.setCursor(47,12); // SOIL 
  screen.print(eraseSoil);
  screen.setCursor(47,45); // MESSAGE
  screen.print(eraseMsg);
}
/*
This will update the values under the headers
on the screen, it calls the 
void clear(T colorBackground, T colorText , int oldText)
function clear the text, this checks if there is a change
in the soil sensor reading and will update the screen if
there is a change
*/
template <class T>
void update(T colorBackground, T colorText)
{
  int soilMoistureReadingBefore = analogRead(SOILMOISTURE); // takes soil moisture 
  int humidityReadingBefore = analogRead(DHT11);
  int tempReadingBefore = analogRead(DHT11);
  screen.setTextColor(colorText, colorBackground);
  screen.setCursor(0,45); //TEMP
  screen.print(tempReadingBefore);
  screen.setCursor(0, 12); //HUM
  screen.print(humidityReadingBefore);
  screen.setCursor(47,12); //SOIL
  screen.print(soilMoistureReadingBefore);
  screen.setCursor(47,45); //MESSAGE
  screen.print("This is a message");

  //int soilMoistureValue = analogRead(SOILMOISTURE); //compares it
  if(/*bool function that that detects a change in a value to the sensors */) //need bool function when change is detected in any of the sesors
  {
    clear(colorBackground, colorText, oldNumber);
    screen.setTextColor(colorText);
    screen.setCursor(0,45);
    screen.print(soilMoistureValue);
    screen.setCursor(0, 12);
    screen.print(soilMoistureValue);
    screen.setCursor(47,12);
    screen.print(soilMoistureValue);
    screen.setCursor(47,45);
    screen.print(soilMoistureValue);
  }
}


void setup() 
{
  Serial.begin(9600);
  screen.begin();
  screen.setFont();
  screen.fillScreen(BLACK);
  screen.setTextColor(WHITE);
  setHeaders();
  update(BLACK,GREEN);

  //Pinmodes
  pinMode(LEDGREEN, OUTPUT);
  pinMode(LEDBLUE, OUTPUT);
  pinMode(LEDRED, OUTPUT);
  pinMode(SOILMOISTURE, INPUT);
}

void loop() 
{
  update(BLACK,GREEN);
  //new comment 
}