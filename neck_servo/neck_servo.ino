#include <Servo.h>

Servo servo1;

String inString = "";

void setup() {
  servo1.attach(9);
  //servo1.setMaximumPulse(2000);
  //servo1.setMinimumPulse(700);

  Serial.begin(9600);

  Serial.println("neck_servo");
}

void loop() {
  // Read serial input:
  while (Serial.available() > 0) {
    int inChar = Serial.read();
    if (isDigit(inChar)) {
      // convert the incoming byte to a char 
      // and add it to the string:
      inString += (char)inChar; 
    }
    // if you get a newline, print the string,
    // then the string's value:
    if (inChar == '\n') {
      Serial.println(inString);

      servo1.write(inString.toInt());

      // clear the string for new input:
      inString = ""; 
    }
  }
}

