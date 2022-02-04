#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <ESPmDNS.h>

#include <AutoConnect.h>

#include "Constants.h"
#include "PreferencesManager.h"

WebServer Server;
AutoConnect Portal(Server); //https://hieromon.github.io/AutoConnect
AutoConnectConfig ACConfig = AutoConnectConfig(MY_METRIC, nullptr);


void SetupNetwork() {
  ACConfig.title = MY_METRIC;
  ACConfig.portalTimeout = 60000;
  ACConfig.autoReconnect = true;
  Portal.config(ACConfig);
  if (Portal.begin()) {
    Serial.println("WiFi connected: " + WiFi.localIP().toString());
    if (MDNS.begin("mymetric")) {
      Serial.println("mDNS Configured: http://mymetric.local/");
      MDNS.addService("http", "tcp", 80);
    }
  }
}

int requestNum = 0;
void handleGenericArgs() { //Handler
  for (int i = 0; i < Server.args(); i++) {

    setSetting(Server.argName(i), Server.arg(i), requestNum);

  }
  Server.sendHeader(LOCATION_HEADER, "/", true); //Redirect to our html web page
  Server.send(302, TEXT_PLAIN, EMPTY);
  requestNum++;
}

void SetupPaths() {
  //    Server.on("/", HTTP_GET, [&]() {
  //        String index = readFile("/index.htm"); //TODO change to LittleFs
  //        if (index == EMPTY) {
  //            Serial.println("index.html does not exist");
  //            Server.send(200, TEXT_PLAIN, "index.html does not exist, please upload it via /edit path");
  //        }
  //        Server.send(200, TEXT_HTML, index);
  //    });

  Server.on("/restart", HTTP_GET, [&]() {
    Server.send(200, TEXT_PLAIN, "Restarting MyMetric");
    Serial.println(F("Restarting ESP via HTTP command"));
    delay(1000);
    ESP.restart();
  });

  Server.on("/getSettings", HTTP_GET, [&]() {
    Serial.println(F("Got getSettings request"));
    Server.send(200, APPLICATION_JSON, getSettings());

  });

  Server.on("/restoreDefaultSettings", HTTP_GET, [&]() {
    Serial.println(F("Got restoreDefaultSettings request"));
    restoreDefaultSettings();
    Server.send(200, TEXT_PLAIN, "Default Settings Restored!");
  });

  Server.on("/setSettings", HTTP_POST, handleGenericArgs);


  Server.onNotFound([&]() {
    Server.sendHeader(LOCATION_HEADER, "/", true); //Redirect to our html web page
    Server.send(302, TEXT_PLAIN, EMPTY);
  });
}

void setup() {
  Serial.begin(115200);
  SetupPreferences();
  SetupPaths();
  SetupNetwork();


}

void loop() {

  if (WiFi.status() == WL_CONNECTED) {
    // Some sketch code for the connected scene is here.
  }
  else {
    // Some sketch code for not connected scene is here.
  }
  Portal.handleClient();
}
