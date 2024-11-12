/*
* Name: Clock and Temp Project
* Author: Victor Huke
* Date: 2024-10-10
* Description: This project uses a DS3231 to measure time and displays the time on an OLED display.
* Additionally, it measures temperature and controls a continuous servo motor's speed based on the temperature.
*/

// Include Libraries
#include <Servo.h>
#include <RTClib.h>
#include <Wire.h>
#include "U8glib.h"

// Init constants
#define DS3231_I2C_ADDR             0x68
#define DS3231_TEMPERATURE_ADDR     0x11
#define LED_PIN 12



const int potPin = A0;
int ThermistorPin = A0;
int Vo;
float R1 = 10000; // value of R1 on board
float logR2, R2, T;
float c1 = 0.001129148, c2 = 0.000234125, c3 = 0.0000000876741;


// Init global variables

// construct objects
RTC_DS3231 rtc;
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);
Servo myservo;  
int pos = 0; 

void setup() {
  // init communication
  u8g.setFont(u8g_font_unifont);
  Serial.begin(9600);
  Wire.begin();
  
  if (!rtc.begin()) {
      Serial.println("Couldn't find RTC");
      while (1);
  }
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));  // Set time to compile time
  
  myservo.attach(9);  // Attach servo to pin 9
  myservo.write(0);

  pinMode(LED_PIN, OUTPUT);
  
 
  
  // Init Hardware

}

void loop() {
  oledWrite(getTime());
  servoWrite(getTemp());
  delay(100);

}


/*
*This function reads time from an ds3231 module and package the time as a String
*Parameters: Void
*Returns: time in hh:mm:ss as String
*/
String getTime(){
  DateTime now = rtc.now(); 
  return (String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second()));
  
}

/*
* This function reads an analog pin connected to an analog temprature sensor and calculates the corresponding temp
*Parameters: Void
*Returns: temprature as float
*/
float getTemp(){
 float tempC = DS3231_get_treg();
  Serial.print("Temperature: ");
  Serial.println(tempC);
  return tempC;
}

/*
* This function takes a string and draws it to an oled display
*Parameters: - text: String to write to display
*Returns: void
*/
void oledWrite(String text){
u8g.firstPage();

  do{
    u8g.drawStr(10, 20, text.c_str());
  } while (u8g.nextPage());
  
}

/*
* takes a temprature value and maps it to corresppnding degree on a servo
*Parameters: - value: temprature
*Returns: void
*/
void servoWrite(float value){

  int speedControl = map(value, 26.5, 27, 0, 180);
  speedControl = constrain(speedControl, 0, 180); 
  myservo.write(speedControl);  
  if (value > 26.5){
    digitalWrite(LED_PIN, HIGH);
  }

  else {
    digitalWrite(LED_PIN, LOW);
  }
}

float DS3231_get_treg() {
  uint8_t temp_msb, temp_lsb;
  int8_t nint;

  Wire.beginTransmission(DS3231_I2C_ADDR);
  Wire.write(DS3231_TEMPERATURE_ADDR);
  Wire.endTransmission();

  Wire.requestFrom(DS3231_I2C_ADDR, 2);
  temp_msb = Wire.read();
  temp_lsb = Wire.read() >> 6;

  if (temp_msb & 0x80) // Check if negative, using two's complement
    nint = temp_msb | ~((1 << 8) - 1);
  else
    nint = temp_msb;

  return (0.25 * temp_lsb + nint);
}





  

  
