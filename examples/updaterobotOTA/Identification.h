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
// Name         : identification.h
// Author       : Minor text modifications by Debinix Team (c).
// Source       : Link to Ralph's YouTube video: https://youtu.be/OaHzlBTUrRQ
// License      : The MIT Licence.
// Version      : Date 2022-10-15.
// Required libs: Install AsyncTCP, ESPAsyncWebServer, and AsyncElegantOTA.
//
// Description : This example shows how to use OTA to update the vocabulary
//               on a previously fielded ESP32 TinyPICO Talkie robot.
//
// NOTE        : This file does NOT need to be touched unless something fails!   
// ----
// What's next : Browse predefined vocabulary with the shell script 'talkie-vocab.sh'. 
//==================================================================================

// Allow OTA software updates
#include <WiFi.h>
#include <AsyncTCP.h>           // https://github.com/me-no-dev/AsyncTCP
#include <ESPAsyncWebServer.h>  // https://github.com/me-no-dev/ESPAsyncWebServer
#include <AsyncElegantOTA.h>    // https://github.com/ayushsharma82/AsyncElegantOTA 

// WiFi debugging
#include <esp_log.h>
#include <esp_wifi.h>

extern String projectTitle;
extern String projectDesc;
extern const char *SSID;
extern const char *PASSWORD;

AsyncWebServer server(80);

// Convert the WiFi (error) response to a string we can understand
const char *wl_status_to_string(wl_status_t status)
{
    switch (status)
    {
    case WL_NO_SHIELD:
        return "WL_NO_SHIELD";
    case WL_IDLE_STATUS:
        return "WL_IDLE_STATUS";
    case WL_NO_SSID_AVAIL:
        return "WL_NO_SSID_AVAIL";
    case WL_SCAN_COMPLETED:
        return "WL_SCAN_COMPLETED";
    case WL_CONNECTED:
        return "WL_CONNECTED";
    case WL_CONNECT_FAILED:
        return "WL_CONNECT_FAILED";
    case WL_CONNECTION_LOST:
        return "WL_CONNECTION_LOST";
    case WL_DISCONNECTED:
        return "WL_DISCONNECTED";
    default:
        return "UNKNOWN";
    }
}

void otaInit()
{

    printf("Setting ESP32 TinyPICO as Station, no power savings, SSID %s\n", SSID);

    esp_log_level_set("wifi", ESP_LOG_VERBOSE);

    if (WiFi.status() == WL_CONNECTED) 
    {
        WiFi.disconnect(true, true);
        printf("WiFi was previously connected - now disconnected\n");
    }

    WiFi.mode(WIFI_STA);
    WiFi.persistent(false);
    WiFi.setAutoReconnect(true);
    WiFi.setSleep(false);
    
    if (WiFi.begin(SSID, PASSWORD))
    {
        printf("WiFi begin success.\n");
    }
    //WiFi.setTxPower(WIFI_POWER_5dBm);
    delay(2000);

    printf("Connecting to WiFi .");
    uint8_t wifiStatus = WiFi.waitForConnectResult();

    // Successful connection?
    if ((wl_status_t)wifiStatus != WL_CONNECTED)
    {
        printf("WiFi Status: %s, exiting\n", wl_status_to_string((wl_status_t)wifiStatus));
        while (1)
            ;
    }

    // Just some information about the Wifi
    printf(
        "\nRunning on SSID %s with IP %s, Channel %d, MAC address %s\n",
        (char *)WiFi.SSID().c_str(),
        (char *)(WiFi.localIP()).toString().c_str(),
        WiFi.channel(),
        (char *)WiFi.macAddress().c_str());

    // This gets printed when you type the IP address followed by /whoami
    server.on("/whoami", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/plain", projectDesc); });

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  printf("Sending response started\n");
                  request->send(
                      200,
                      "text/html",
                      R"(
        <!DOCTYPE HTML>
        <head><title>)" +
                          String(projectTitle) +
                          R"(</title></head>
        <body style='font-size:1.1em;'>
          <h3>Arduino ESP OTA Home Page</h3>

          <div>Congratulations! You've reached your )" +
                          String(projectTitle) +
                          R"( ESP32 TinyPICO device on IP )" +
                          String((char *)(WiFi.localIP()).toString().c_str()) +
                          R"(</div>

         <fieldset style="margin:20px 5px 20px 5px;border:1px;border-radius:5px;border:1px solid darkgray;background-color:white">
          <legend style="font-size:0.8em;">Project description:</legend>
            <div style="font-size:0.8em;background-color:#EEEEEE;padding:5px;border-radius:10px;">)" +
                          String(projectDesc) +
                          R"(</div>
          </fieldset>

          <p>To update your device from the Arduino IDE choose:
          <ul>
            <li><b>Sketch->Export compiled Binary</b>
            <li>then find the sketch folder by choosing 
            <li><b>Sketch->Show Sketch Folder</b> and then
            <li>use the 'update' link below to navigate to your '.bin' file to upload.
          </ul>
          </p>
          
          <p> To update your code type this into your address bar:<br /> 
            <a href='http://)" +
                          String((char *)(WiFi.localIP()).toString().c_str()) +
                          R"(/update' target='_blank'>http://)" + String((char *)(WiFi.localIP()).toString().c_str()) +
                          R"(/update</a> <br />
            or just click this link.
          </p>
        </body>
        </html>
      )");
                  printf("Sending response ends\n");
              });

    // Starting Async OTA web server
    AsyncElegantOTA.begin(&server);
    server.begin();
}
