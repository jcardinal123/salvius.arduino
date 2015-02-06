#include <Servo.h>

Servo servo1;

const String NAME = "neck_servo";

String inString = "";

void setup() {
  servo1.attach(9);
  //servo1.setMaximumPulse(2000);
  //servo1.setMinimumPulse(700);

  Serial.begin(9600);
}

void loop() {
  // Read serial input:
  while (Serial.available()) {
    int inChar = Serial.read();

    //if (isDigit(inChar)) {
    if (inChar >= '0' && inChar <= '9') {
      // convert the incoming byte to a char and add it to the string:
      inString += (char)inChar;
    }
    
      if (inChar == ':') {
        // Print the board name to identify with python code
        Serial.println(NAME);
      }

      if (inChar == '\n') {
        // if you get a newline, print the string, then the string's value:
        Serial.println(inString);
        servo1.write(inString.toInt());
        // clear the string for new input
        inString = "";
      }

  }
}





