#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1331.h>
#include <SPI.h>
#include <Adafruit_I2CDevice.h>
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
This function will send valued to
the screen and can also be used to 
clear the data under the headers. 
*/
template <class T>
void sendValuesToScreen(T colorText, int temp, int hum, int soil, char* message)
{
  screen.setTextColor(colorText);
  screen.setCursor(0,12);
  screen.print(temp);
  screen.setCursor(47,12);
  screen.print(hum);
  screen.setCursor(0,45);
  screen.print(soil);
  screen.setCursor(47, 45);
  screen.print(message);
}
/*
will update the specific value under temp
*/
template <class T>
void changeTempOnScreen(T colorText, int temp)
{
  screen.setTextColor(colorText);
  screen.setCursor(0,12);
  screen.print(temp);
}
/*
will update the specific value under hum
*/
template <class T>
void changeHumOnScreen(T colorText, int hum)
{
  screen.setTextColor(colorText);
  screen.setCursor(47,12);
  screen.print(hum);
}
/*
will update soil
*/
template <class T>
void changeSoilOnScreen(T colorText, int soil)
{
  screen.setTextColor(colorText);
  screen.setCursor(0,45);
  screen.print(soil);
}
/*
will update message
*/
template <class T>
void changeMessageOnScreen(T colorText, char* message)
{
  screen.setTextColor(colorText);
  screen.setCursor(47,45);
  screen.print(message);
}

void setup()
{
  screen.begin();
  screen.setFont();
  screen.fillScreen(RED);
  screen.setTextColor(YELLOW);
  setHeaders();
}
void loop()
{
  char str[] = "WARNING!";
  sendValuesToScreen(GREEN,1,2,3, str);
  delay(500);
  //sendValuesToScreen(RED,1,2,3, str);
  //delay(500);
  changeTempOnScreen(RED,1);
  //delay(500);
  changeTempOnScreen(BLACK, 94);
  delay(500);
  changeTempOnScreen(RED, 94);
  //delay(500);

}