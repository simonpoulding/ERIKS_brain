/*
Connects as a station to an access point and gets its own IP using DHCP
*/

const char *MY_SSID="Sweethome";
const char *MY_PASS="nSJc3SF5XxrJOlb9";
const char *HOST="192.168.0.15";
const char *PATH="/";
// const char *PARAMS="?p=42";
const char *OPTIONS="";

// For the comms with the WIFI module we need SoftSerial
#include <SoftwareSerial.h>

// Piccolino's WIFI module library
#include <Piccolino_WIFI.h>

Piccolino_WIFI wifi; // our WIFI object

// For load gauge
#include "HX711.h"

HX711 scale(9, 10);

float calibration_factor = -103100; //-7050 worked for my 440lb max scale setup

void debug(const __FlashStringHelper *msg) {
  Serial.print(msg);
}

void setup(void) {

    byte local_buff[128]; // just to show our IP

  Serial.begin(9600);
  delay(1000); // give time for bootloader to settle
  
  debug(F("Wifi Begin ...\n"));
  wifi.begin();  

  delay(1000);
  debug(F("Loading script ...\n")); 
  wifi.load("CoffeeStatus.lua");

  delay(1000);
  debug(F("WIFI Connect ...\n"));
  wifi.Connect((char *)MY_SSID,(char *)MY_PASS); // connect - ip will be in local_buff
  debug(F("WIFI Connected ...\n"));

  scale.set_scale();
  scale.tare(); //Reset the scale to 0
  scale.set_scale(calibration_factor); //Adjust to this calibration factor
}

void loop(void) {

  byte local_buff[128]; // just to show our IP
  
  debug(F("Begin loop ...\n"));
  delay(1000);

  debug(F("After delay ...\n"));
  


//  display.clear();
//  display.setTextSize(1);
//  display.setCursor(0,0);

//  debug(F("WIFI Disconnect ...\n"));
//  wifi.disconnect();  // disconnect just in case


          
    debug(F("Reading weight...\n"));
  
    // now we can process the input and act upon it


      float weight = scale.get_units();
      float displayedweight = weight;
      if (displayedweight < 0.0) {
       displayedweight = 0.0;
      }

      char *paramweight = "42";
 //      String paramweight = String(displayedweight);

      Serial.println((char *)paramweight);

//      String params = String("?w=" + paramweight);
      char *params="?w=3";

    debug(F("Sending weight...\n"));

      wifi.getFeed((char *)HOST, (char *)PATH, (char *)params, (char *)OPTIONS);

      delay(1000);

    debug(F("Checking WIFI available...\n"));
      if(wifi.available()) {    
      debug(F("Getting response...\n"));
        wifi.getResponse(); // places response in the serial buffer
      debug(F("Got response...\n"));

//    debug(F("Disabling WIFI...\n"));
//    wifi.disable();  

  }
}
