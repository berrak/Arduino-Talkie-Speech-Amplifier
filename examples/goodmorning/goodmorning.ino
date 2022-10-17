//==================================================================================
// Name        : goodmorning.ino
// Author      : Created by Debinix Team (c).
// License     : GPL-3.0
// Version     : Date 2022-10-15.
// Description : This example shows how to use Talkie's predefined vocabulary
//               with the 'Arduino Talkie Speech Amplifier' and ESP32 TinyPICO.
//
// What's next : Browse predefined vocabulary with the shell script 'talkie-vocab.sh'. 
//==================================================================================

#include <Talkie.h>
#include "Vocab_US_Clock.h"

Talkie voice;

const int volDAC = 26;   // GPIO26 controls speaker volume

void setup() {
    Serial.begin(115200);
    delay(1000);

    dacWrite(volDAC, 255); // 8bit DAC '255' = max voltage/volume out, i.e. 3.3V.

    Serial.println("Setup completed...");
}

void loop() {

    voice.say(spc_GOOD);
    voice.say(spc_MORNING);
    delay(1000);
    voice.say(spc_GOOD);  
    voice.say(spc_AFTERNOON);
    delay(1000);
    voice.say(spc_GOOD);  
    voice.say(spc_EVENING);

    delay(3000);  
}
