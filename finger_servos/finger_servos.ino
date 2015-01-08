/*************************************************** 
 * This is an example for our Adafruit 16-channel PWM & Servo driver
 * Servo test - this will drive 16 servos, one after the other
 * 
 * Pick one up today in the adafruit shop!
 * ------> http://www.adafruit.com/products/815
 * 
 * These displays use I2C to communicate, 2 pins are required to  
 * interface. For Arduino UNOs, thats SCL -> Analog 5, SDA -> Analog 4
 * 
 * Adafruit invests time and resources providing this open source code, 
 * please support Adafruit and open-source hardware by purchasing 
 * products from Adafruit!
 * 
 * Written by Limor Fried/Ladyada for Adafruit Industries.  
 * BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
#include "Adafruit_PWMServoDriver.h"

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);

// Depending on your servo make, the pulse width min and max may vary, you 
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you have!
#define SERVOMIN 150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX 400 // this is the 'maximum' pulse length count (out of 4096)

void setup() {
  Serial.begin(9600);
  pwm.begin();

  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
}

char servoLetter = ' ';
String inString = "";

int letterToNumber(char letter) {
  
  String letters = "abcdefghijklmnop";
  return letters.indexOf(letter);
}

void loop() {

  while (Serial.available() > 0) {
    
    int inChar = Serial.read();
    
    if (isDigit(inChar)) {
      // convert the incoming byte to a char and add it to the string
      inString += (char)inChar;
    } else if (inChar != '\n') {
      servoLetter = (char)inChar;
    }
    
    if (inChar == '\n') {
      Serial.println(inString);
      Serial.println(letterToNumber(servoLetter));


      int servonum = letterToNumber(servoLetter);
      
      for (int pulselen = SERVOMIN; pulselen < inString.toInt(); pulselen++) {
        pwm.setPWM(servonum, 0, pulselen);
      }
      // clear the string for new input
      inString = "";
    }

  }

}


