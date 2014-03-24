
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <WString.h>

//BLE Mini is connected to pin 2 and 3.
SoftwareSerial BLEMini(2, 3);
String serialCommand = "";   
boolean stringComplete = false;
unsigned char buf[16] = {0};
unsigned char len = 0;
int nowState;

void setup()
{
  BLEMini.begin(57600);
  
  Serial.begin(57600);
  serialCommand.reserve(64);
  nowState = 0;
}


void loop()
{
  BLEMiniRX();
  parseCommand();
  
    
  if (nowState == 1) {
  BLEMini.write("<0000,00,0000>\r\n");delay(100);
  BLEMini.write("<0000,01,0000>\r\n");delay(100);
  BLEMini.write("<0000,02,0000>\r\n");delay(100);
  BLEMini.write("<0000,03,0000>\r\n");delay(100);
  BLEMini.write("<0000,04,0000>\r\n");delay(100);
  BLEMini.write("<0001,00,0000>\r\n");delay(100);
  BLEMini.write("<0002,01,0000>\r\n");delay(100);
  BLEMini.write("<0003,02,0000>\r\n");delay(100);
  BLEMini.write("<0004,03,0000>\r\n");delay(100);
  BLEMini.write("<0005,04,0000>\r\n");delay(100);  
  }
  delay(10);

}
void parseCommand() 
{
  if (stringComplete) {
    Serial.println(serialCommand); 
    String command=serialCommand.substring(0,4);
    if (command.equals("HOST")) {
      //Serial.println("Got it");
      nowState = 1;
    }
   if (command.equals("STOP")) {
      //Serial.println("Got it");
      nowState = 0;
    }
  }
  serialCommand = "";
  stringComplete = false; 
}
void BLEMiniRX()
{
  while ( BLEMini.available()){
    // get the new byte:
    char inChar = (char)BLEMini.read(); 
    // add it to the inputString:
    serialCommand += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    } 
  }
}

void serialEvent() 
{
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    // add it to the inputString:
    serialCommand += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    } 
  }
}

