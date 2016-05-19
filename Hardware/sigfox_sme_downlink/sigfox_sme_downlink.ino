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
  setConfigurationMode();
  delay(1000);
  getID();
}

void loop() {
  
  //Here we send simple message using Sigfox (uplink) when the button one is pressed
  if (isButtonOnePressed()) {
    //sendSimpleSigfoxMessage("CAFE");
    getLedStatus();
    }

  //Here we send a message and we wait to receive the ACK using Sigfox (downlink) when the button two is pressed
  if (isButtonTwoPressed()) {
     sendAndReceiveSigfoxMessage();
   }

}

int getLedStatus(){
  ledRedLight(HIGH);
  delay(500);
  int led=0;
  SerialUSB.println("PIN_LED_RED");
  SerialUSB.println(digitalRead(PIN_LED_RED));
  SerialUSB.println("PIN_LED_TXL");
  SerialUSB.println(digitalRead(PIN_LED_TXL));
  
  return led;
}

void sendSimpleSigfoxMessage(String frame){
  resetLEDs();
  String status = "";
  char output;
  if(DEBUG){
    SerialUSB.print("AT$SF=");
    SerialUSB.println(frame);
  }
  
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
  
  bool isStatusSet = false;
  bool isDataReceived = false;
  bool startData = false;
  String status = "";
  String temp = "";
  String data = "";
  char output;

  //First we start to send a message here the message is 0000 and we add ",1" to ask for a downlink
  if(DEBUG){
    SerialUSB.println("AT$SF=0000,1\r");
  }
  
  delay(1000);
  SigFox.print("AT$SF=0000,1\r");
  while (!SigFox.available()){
     blink();
  }
  while(SigFox.available()){

    //The message received will be like OK\r+RX=0000000000000001\r+RX END
    //We will get the status from this message and the data (note that 0xD correspond to \r)
    output = SigFox.read();
    if(DEBUG){
      //SerialUSB.print(output);
      SerialUSB.print(output, HEX);
    }
    if(!isStatusSet){
      if(output == 0xD){
        isStatusSet = true;
      }else{
        status += output;
      }
    }else if(!startData){
      temp += output;
      
      if(temp == "+RX="){
        startData = true;
        temp = "";
      }
    }else if(!isDataReceived){
      if(output == 0xD){
        isDataReceived = true;
      }else{
        data += output;
      }
    }
    delay(10);
  }
  if(DEBUG){
    SerialUSB.println("Status \t");
    SerialUSB.println(status);
    SerialUSB.println("data \t");
    SerialUSB.println(data);
  }
  
   if (status == "OK"){
    //Success :)
    ledGreenLight(HIGH);
  }
  else{
    ledRedLight(HIGH);
  }

  delay(1000);
  setLedFromBackendMessage(data);
}



//This function gives you the device ID
String getID(){
  setConfigurationMode();
  resetLEDs();
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

void setConfigurationMode(){
  resetLEDs();
  String status = "";
  char output;
  if(DEBUG){
    SerialUSB.println("Configuration Mode");
  }
  
  delay(1000);
  SigFox.print("+++");
  while (!SigFox.available()){
     blink();
  }
  while(SigFox.available()){
    output = (char)SigFox.read();
    status += output;
    delay(10);
  }
  SerialUSB.println(status);
   if (status == "OK\r"){
    //Success :)
    ledBlueLight(HIGH);
  }
  else{
    ledRedLight(HIGH);
  }
  
  
}

void setLedFromBackendMessage(String data){
  if(data=="0000000000000001"){
    resetLEDs();
    ledRedLight(HIGH);
  }
  if(data=="0000000000000002"){
    resetLEDs();
    ledGreenLight(HIGH);
  }
  if(data=="0000000000000003"){
    resetLEDs();
    ledBlueLight(HIGH);
  }
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

