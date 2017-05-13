// For the OLED, we need I2C
#include <Wire.h>

// For the FRAM we need SPI
#include <SPI.h>

// I2C OLED library
#include <Piccolino_OLED.h>

#include "HX711.h"

Piccolino_OLED display; // our OLED object ...

#define DOUT  3
#define CLK  4 // for Picollino

HX711 scale(DOUT, CLK);

float calibration_factor = -103100; //-7050 worked for my 440lb max scale setup

void setup() {

  display.begin();

  scale.set_scale();
  scale.tare(); //Reset the scale to 0
  scale.set_scale(calibration_factor); //Adjust to this calibration factor

}


void loop () {


   display.clear();
   display.setCursor(0,16); // skip yellow portion of display
    
   display.setTextColor(WHITE);
   display.setTextSize(1);
   display.print("Weight: ");
   display.print(scale.get_units(), 1);
   display.println();
   
   display.update();
   delay(100);

}
