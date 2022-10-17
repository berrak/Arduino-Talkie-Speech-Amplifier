// MIT License

// Copyright (c) 2021 Ralph Bacon 

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

//==================================================================================
// Name         : updaterobotOTA.ino
// Author       : Modified original by Debinix Team (c).
// Source       : Link to Ralph's YouTube video: https://youtu.be/OaHzlBTUrRQ
// License      : The MIT Licence.
// Version      : Date 2022-10-15.
// Required libs: Install AsyncTCP, ESPAsyncWebServer, and AsyncElegantOTA.
//
// Description : This example shows how to use OTA to update the vocabulary
//               on a previously fielded ESP32 TinyPICO Talkie robot.
// NOTE        : Make changes in this file only.   
// ----
// What's next : Browse predefined vocabulary with the shell script 'talkie-vocab.sh'. 
//==================================================================================

#include <TinyPICO.h>

#include <Talkie.h>
#include "Vocab_US_Clock.h"
#include "Vocab_US_Large.h"

#include "Identification.h"     // OTA stuff - no changes are required

Talkie voice;

// Initialise the TinyPICO Dotstar library
TinyPICO tp = TinyPICO();

// Set your WiFi credentials!
const char *SSID = "FW114";
const char *PASSWORD = "";

// OTA stuff included here
String projectTitle = "Arduino Talkie Speech Amplifier";
String projectDesc = "ESP32 TinyPICO demo for updates of a Talkie robot device! <p>You can write text here or <b>html</b>.</p> ";

const int volDAC = 26;   // GPIO26 controls speaker volume

void setup()
{
    // 8bit DAC '255' = max voltage/volume out, i.e. 3.3V. 
    dacWrite(volDAC, 255); 

    // Everything for OTA updates
    otaInit();
}


void loop()
{
    // Variables just for this function
    static unsigned long counter = 1;
    static unsigned long prevMillis = 0;

    // We'll update a counter every few seconds
    if (millis() - prevMillis > 3000)
    {
        printf("Counter is now %ld\n", ++counter);
        prevMillis = millis();
    }

    // Comment/uncomment each section in turn
    //---------------------------------------
    // One version of code
//    tp.DotStar_SetPixelColor( 0, 255, 0 );  // Fix green 
//    voice.say(spc_GOOD);
//    voice.say(spc_MORNING);
//    delay(2500);

    // New version of code 
 tp.DotStar_SetPixelColor( 255, 0, 0 );  // Fix red
 voice.say(sp2_DANGER);
 voice.say(sp2_DANGER);
 voice.say(sp2_RED);
 voice.say(sp2_ALERT);
 delay(2500);

}
