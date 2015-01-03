#include "TTS.h"

// The name of this board used to identify it on the serial port
const String NAME = "text_to_speech";

// speech output is digital pin 10
TTS tts;

//char input[8] = {'a', 'r', 'd', 'u', 'i', 'n', 'o'};
char input[8];
int index = 0;

void setup() {
  // higher values = lower voice pitch
  tts.setPitch(16);

  Serial.begin(115200);
}

char line[80];
int pos = 0;

void loop() {

  if (Serial.available() > 0) {

    Serial.println(NAME);

    char c = (char)Serial.read();
    if (c == '\n') {
      line[pos++] = 0;
      if (line[0] != '+') {
        Serial.println(line);
        tts.sayText(line);
      }
      pos = 0;
    } else {
      line[pos++] = c;
    }

  }

  delay(100);
}

