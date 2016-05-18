/*
 *  Subject: This project demonstrate how to realise a downlink using the smarteverything board.
 *           Depending on the ACK value, the led will change its color when it is received by the SmartEveryThing board.
 *           The request will be asked by the card every 10 minutes or when the button is pressed.
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
  //LED & User Button are already initialized by the SME core

  // Init UART devices
  SerialUSB.begin(115200);
  SigFox.begin(19200);
  delay(100);
  //setConfigurationMode();
  delay(1000);
  getID();
}

void loop() {
  
  //Here we send simple message using Sigfox (uplink) when the button one is pressed
  if (isButtonOnePressed()) {
    sendSimpleSigfoxMessage("CAFE");
    }

  //Here we send a message and we wait to receive the ACK using Sigfox (downlink) when the button two is pressed
  if (isButtonTwoPressed()) {
     sendAndReceiveSigfoxMessage();
   }

}

void sendSimpleSigfoxMessage(String frame){
  resetLEDs();
  String status = "";
  char output;
  SerialUSB.print("AT$SF=");
  SerialUSB.println(frame);
  SigFox.print("AT$SF=");
  SigFox.print(frame);
  SigFox.print("\r");
  while (!SigFox.available()){
     blink();
  }
  while(SigFox.available()){
    output = (char)SigFox.read();
    status += output;
    delay(10);
  }
  if(DEBUG){
    SerialUSB.print("Status \t");
    SerialUSB.println(status);
  }
  
 if (status == "OK\r"){
  //Success :)
  ledGreenLight(HIGH);
  }
 else{
  ledRedLight(HIGH);
  }
}

void sendAndReceiveSigfoxMessage(){
  resetLEDs();
  String status = "";
  char output;
  
  SerialUSB.println("AT$SF=6e69636f6c7363,1\r");

  delay(1000);
  SigFox.print("AT$SF=6e69636f6c7363,1\r");
  while (!SigFox.available()){
     blink();
  }
  while(SigFox.available()){
    output = (char)SigFox.read();
    status += output;
    delay(10);
  }
  SerialUSB.println("Status \t");
  SerialUSB.println(status);
   if (status == "OK\r"){
    //Success :)
    ledGreenLight(HIGH);
  }
  else{
    ledRedLight(HIGH);
  }
  
  
}

//This function gives you the device ID
String getID(){
  String id = "";
  char output;
  
  SigFox.print("AT$ID\r");
  while (!SigFox.available()){
     blink();
  }
  
  while(SigFox.available()){
    output = (char)SigFox.read();
    id += output;
    delay(10);
  }
  
  if(DEBUG){
    SerialUSB.println("Sigfox Device ID: ");
    SerialUSB.println(id);
  }
  
  return id;
}


void blink(){
  ledBlueLight(HIGH);
  delay(100);
  ledBlueLight(LOW);
  delay(200);
}

void resetLEDs(){
  ledRedLight(LOW);
  ledGreenLight(LOW);
  ledBlueLight(LOW);
}

