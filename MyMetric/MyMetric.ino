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




void rootPage() {
  char content[] = "Hello, world";
  Server.send(200, "text/plain", content);
}

void setup() {
  Serial.begin(115200);
  SetupPreferences();

  Server.on("/", rootPage);
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

void loop() {

  if (WiFi.status() == WL_CONNECTED) {
    // Some sketch code for the connected scene is here.
  }
  else {
    // Some sketch code for not connected scene is here.
  }
  Portal.handleClient();
}
