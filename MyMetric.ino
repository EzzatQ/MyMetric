#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <ESPmDNS.h>

#include <AutoConnect.h>

#include "Constants.h"
#include "PreferencesManager.h"
#include "FileManager.h"

WebServer Server;
AutoConnect Portal(Server); //https://hieromon.github.io/AutoConnect
AutoConnectConfig ACConfig = AutoConnectConfig(MY_METRIC, nullptr);
AutoConnectAux auxUpload;
AutoConnectAux auxBrowse;

String postUpload(AutoConnectAux& aux, PageArgument& args) {
  String  content;
  AutoConnectFile&  upload = auxUpload["upload_file"].as<AutoConnectFile>();
  AutoConnectText&  aux_filename = aux["filename"].as<AutoConnectText>();
  AutoConnectText&  aux_size = aux["size"].as<AutoConnectText>();
  AutoConnectText&  aux_contentType = aux["content_type"].as<AutoConnectText>();
  // Assignment operator can be used for the element attribute.
  aux_filename.value = upload.value;
  aux_size.value = String(upload.size);
  aux_contentType.value = upload.mimeType;
  return String();
}

void SetupNetwork() {
  ACConfig.title = MY_METRIC;
  
  ACConfig.portalTimeout = 60000;
  ACConfig.autoReconnect = true;
  auxUpload.load(PAGE_UPLOAD);
  auxBrowse.load(PAGE_BROWSE);
  Portal.join({ auxUpload, auxBrowse });
  auxBrowse.on(postUpload);
  Portal.config(ACConfig);
  if (Portal.begin()) {
    Serial.println("WiFi connected: " + WiFi.localIP().toString());
    if (MDNS.begin("mymetric")) {
      Serial.println("mDNS Configured: http://mymetric.local/");
      MDNS.addService("http", "tcp", 80);
    }
  }
}

void handleGenericArgs() { //Handler
  for (int i = 0; i < Server.args(); i++) {
    setSetting(Server.argName(i), Server.arg(i));
  }
  Server.sendHeader("Access-Control-Allow-Origin", "*");
  Server.send(200, TEXT_PLAIN, EMPTY);
}

void SetupPaths() {
  Server.on("/", HTTP_GET, [&]() {
    String index = readFile("/index.html"); //TODO change to LittleFs
    Server.sendHeader("Access-Control-Allow-Origin", "*");
    if (index == EMPTY) {
      Serial.println("index.html does not exist");
      Server.send(200, TEXT_PLAIN, "index.html does not exist, please upload it via /edit path");
    }
    Server.send(200, TEXT_HTML, index);
  });

  Server.on("/restart", HTTP_GET, [&]() {
    Server.sendHeader("Access-Control-Allow-Origin", "*");
    Server.send(200, TEXT_PLAIN, "Restarting MyMetric");
    Serial.println(F("Restarting ESP via HTTP command"));
    delay(1000);
    ESP.restart();
  });

  Server.on("/getSettings", HTTP_GET, [&]() {
    Serial.println(F("Got getSettings request"));
    Server.sendHeader("Access-Control-Allow-Origin", "*");
    Server.send(200, APPLICATION_JSON, getSettings());

  });

  Server.on("/restoreDefaultSettings", HTTP_GET, [&]() {
    Serial.println(F("Got restoreDefaultSettings request"));
    Server.sendHeader("Access-Control-Allow-Origin", "*");
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
  SetupFileManager();
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
