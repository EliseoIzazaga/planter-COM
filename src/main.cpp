#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1331.h>
#include <SPI.h>
#include <Adafruit_I2CDevice.h>
//#include <String.h>
#include <DHT_U.h>

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

#define DHT11PIN 4

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
/*
will read from DHT11 and print on screen if different from the last reading
it uses pointers, and may need to be rewritten to accomodate the arduino's nature
this was written with the implication that the arduino was going to handle global
variables well but it does not.... (continued in loop())
*/
void readDHT11(float* temperature, float* humidity, DHT dht)
{
  float c = dht.readTemperature();
  float f = dht.readTemperature(true);
  float h = dht.readHumidity();
  
  if (isnan(h) || isnan(c) || isnan(f))
  {
    char err[] = "Could not read DHT11";
    changeHumOnScreen(RED, '*');
    changeTempOnScreen(RED, '*');
    changeMessageOnScreen(RED,err);
    return;
  }
  else if(f == *temperature || h == *humidity)
  return;
  else
  {
    changeTempOnScreen(BLUE,*temperature);
    changeHumOnScreen(BLUE, *humidity);
    *temperature = f;
    *humidity = h;
    changeHumOnScreen(WHITE, *humidity);
    changeTempOnScreen(WHITE, *temperature);
  }  
}

DHT dht(DHT11PIN, DHT11);
void setup()
{
  dht.begin();
  Serial.begin(9600);
  screen.begin();
  screen.setFont();
  screen.fillScreen(BLUE);
  screen.setTextColor(WHITE);
  setHeaders();
}
 void loop()
{
  //delay(2000);
  /*
  given what we have we essentially made an infinite loop within a loop, an idea is to make a button
  that turns off and on the DHT11, but for now it works well and we will leave it as is unless some
  one else has a better idea of how to handle this.
  */
  float* humAddr;
  float* tempAddr;
  float hum;
  float temp;
  humAddr = &hum;
  tempAddr = &temp;
  while(true)
  {
    delay(2000);
    readDHT11(tempAddr, humAddr, dht);
  }
  
  //temp = 0;
  //hum = 0;
  //delay(2000);
  //readDHT11(temp, hum, dht);
  //char str[] = "Test1";
  //sendValuesToScreen(BLACK,94,2,3, str);
  //delay(500);
  //sendValuesToScreen(RED,1,2,3, str);
  //delay(500);
  //changeTempOnScreen(BLUE,1);
  //delay(500);
  //changeTempOnScreen(BLUE, 94);
  //delay(500);
  //changeTempOnScreen(BLACK, 94);
  //delay(500);


  //delay(2000);
  //sendValuesToScreen(WHITE, dht.readTemperature(true), dht.readHumidity(),0,str);
  /*
  //hum = dht.readHum 
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
*/  
}

