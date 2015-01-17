#include <SoftwareSerial.h>

#define rxPin 2    // Serial input (connects to Emic 2 SOUT)
#define txPin 3    // Serial output (connects to Emic 2 SIN)
#define ledPin 13  // Most Arduino boards have an on-board LED on this pin

// set up a new serial port
SoftwareSerial emicSerial =  SoftwareSerial(rxPin, txPin);


String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete


// The name of this board used to identify it on the serial port
const String NAME = "text_to_speech";

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);

  // set the data rate for the SoftwareSerial port
  emicSerial.begin(9600);
  Serial.begin(9600);
  
  digitalWrite(ledPin, LOW);  // turn LED off

  // reserve 200 bytes for the inputString:
  inputString.reserve(200);

  /*
    When the Emic 2 powers on, it takes about 3 seconds for it to successfully
    intialize. It then sends a ":" character to indicate it's ready to accept
    commands. If the Emic 2 is already initialized, a CR will also cause it
    to send a ":"
  */

  emicSerial.print('\n');             // Send a CR in case the system is already up
  while (emicSerial.read() != ':');   // When the Emic 2 has initialized and is ready, it will send a single ':' character, so wait here until we receive it
  delay(10);                          // Short delay
  emicSerial.flush();                 // Flush the receive buffer
}

void loop() {
  // print the string when a newline arrives:
  if (stringComplete) {

    Serial.println(inputString);

    // Speak some text
    emicSerial.print('S');
    emicSerial.print(inputString);  // Send the desired string to convert to speech
    emicSerial.print('\n');
    digitalWrite(ledPin, HIGH);         // Turn on LED while Emic is outputting audio
    while (emicSerial.read() != ':');   // Wait here until the Emic 2 responds with a ":" indicating it's ready to accept the next command
    digitalWrite(ledPin, LOW);
    
    delay(500);    // 1/2 second delay

    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    } 
  }
}

