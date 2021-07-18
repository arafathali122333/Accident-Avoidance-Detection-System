#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();
TinyGPSPlus gps;
SoftwareSerial ss(4, 5);
SoftwareSerial gsm(2,3);
void setup(void)
{
  Serial.begin(9600);
  ss.begin(9600);
  if(!accel.begin())
  {
    while(1);
  }
}
void loop(void)
{
  {while (ss.available() > 0)
    if (gps.encode(ss.read()))
      displayInfo();
  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while(true);
  } } 
  
  if (gps.location.isValid())
  {
     sensors_event_t event; 
     accel.getEvent(&event);
     if(event.acceleration.x < -2 || event.acceleration.x > 0 ||
       event.acceleration.y < -3 || event.acceleration.y > 0 || event.acceleration.z < 9)
       {
          Serial.begin(9600);
          gsm.begin(9600);
          gsm.println("AT+CMGF=1");
          delay(1000);
          gsm.println("AT+CMGS=\"+919486701501\"\r"); //replace x by your number
          delay(1000);
          gsm.println("Accident Alert...");
          gsm.println(" ");
          gsm.println("The person met with an accident");
          gsm.println("Save as soon as possible");
          gsm.println(" ");
          gsm.println("UTC Date => ");
          gsm.print(gps.date.month());
          gsm.print("/");
          gsm.print(gps.date.day());
          gsm.print("/");
          gsm.print(gps.date.year());
          gsm.println(" ");
          gsm.println("UTC Time => ");
          gsm.print(gps.time.hour());
          gsm.print(":");
          gsm.print(gps.time.minute());
          gsm.print(":");
          gsm.print(gps.time.second());
          gsm.println(" ");
          gsm.println("https://maps.google.com/maps?&z=15&mrt=yp&t=k&q=");
          gsm.print(gps.location.lat(),6);
          gsm.print("+");
          gsm.print(gps.location.lng(),6);
          delay(200);
          gsm.println((char)26);
          delay(1000);
          exit(0);
       }
  }
 
}
void displayInfo()
{
  sensors_event_t event; 
     accel.getEvent(&event);
  Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print("  ");
     Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  ");
     Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print("  ");Serial.println("m/s^2 ");
     delay(500);
  Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
  }
  else
  {
    Serial.print(F("INVALID"));
  }
  Serial.print(F("  Date=>"));
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
    Serial.print("  Time=>");
    Serial.print(gps.time.hour());
    Serial.print(":");
    Serial.print(gps.time.minute());
    Serial.print(":");
    Serial.print(gps.time.second());
  }
  else
  {
    Serial.print(F("INVALID"));
  }
  Serial.println();
}
