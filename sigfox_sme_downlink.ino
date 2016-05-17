/*
 *  Subject: This project demonstrate how to realise a downlink using the smarteverything board.
 *           Depending on the ACK value, the led will change its color when it is received by the SmartEveryThing board.
 *           The request will be asked by the card every 10 minutes or when the button is pushed.
 *  
 *  Created by: Louis Moreau
 *  Date: 17 May 2016
 *  
 *  
 *  Notes: 
 *  Since 30 June 2015, the smarteverything libs have been added in the library manager https://github.com/arduino/Arduino/issues/3438
 *  The SigFox class is available through the AmelTech Core https://github.com/ameltech/sme-arduino-core
 * 
 */


#include <Wire.h>
#include <Arduino.h>
#define DELAY 600000 // Set the delay to 10 minutes (10 min x 60 seconds x 1000 milliseconds)
#define DEBUG 1 // Switch between 0 (no debug) or 1 (debug)


void setup() {
  SerialUSB.begin(115200);
  SigFox.begin(19200);
  
}

void loop() {
  // put your main code here, to run repeatedly:

}

