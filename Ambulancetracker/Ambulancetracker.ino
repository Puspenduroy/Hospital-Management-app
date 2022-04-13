//Viral Science www.viralsciencecreativity.com www.youtube.com/c/viralscience
//Realtime GPS Tracker with Nodemcu ESP8266
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
//#define BLYNK_PRINT Serial
//#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h>                 
#include <FirebaseArduino.h>                    
#define FIREBASE_HOST "hospital-45085-default-rtdb.firebaseio.com"      
#define FIREBASE_AUTH "izYUnFvjs0BEiK4zJxrkPHkMDOdxThGObCHWsoWN"            
#define WIFI_SSID "vivo 1718"                                  
#define WIFI_PASSWORD "santasreeroy@25"          
static const int RXPin = 4, TXPin = 5;   // GPIO 4=D2(conneect Tx of GPS) and GPIO 5=D1(Connect Rx of GPS
static const uint32_t GPSBaud = 9600; //if Baud rate 9600 didn't work in your case then use 4800
TinyGPSPlus gps; // The TinyGPS++ object
SoftwareSerial ss(RXPin, TXPin);  // The serial connection to the GPS device
float spd;       //Variable  to store the speed
float sats;      //Variable to store no. of satellites response
String bearing;  //Variable to store orientation or direction of GPS


//unsigned int move_index;         // moving index, to be used later
unsigned int move_index = 1;       // fixed location for now
  

void setup()
{
  Serial.begin(115200);
  Serial.println();
  ss.begin(GPSBaud);
  //timer.setInterval(5000L, checkGPS); // every 5s check if GPS is connected, only really needs to be done once
}

void checkGPS(){
  if (gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
     
  }
}

void loop()
{
    while (ss.available() > 0) 
    {
      // sketch displays information every time a new sentence is correctly encoded.
      if (gps.encode(ss.read()))
        displayInfo();
  }
}

void displayInfo()
{ 
  if (gps.location.isValid() ) 
  {    
    float latitude = (gps.location.lat());     //Storing the Lat. and Lon. 
    float longitude = (gps.location.lng()); 
    Firebase.setFloat ("Latitude",latitude);
    Firebase.setFloat ("Longitude",longitude);
   
  }
  
 Serial.println();
}
