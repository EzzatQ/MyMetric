#ifndef PREFERENCES_MANAGER_H
#define PREFERENCES_MANAGER_H

#include <vector>

#include <Preferences.h> // https://microcontrollerslab.com/save-data-esp32-flash-permanently-preferences-library/#Preferences.h-Example-1:-Save/Read-key:-value-pairs
#include "ArduinoJson.h"
#include "Constants.h"
#include "Utils.h"
#define DEBUG 1

Preferences preferences;


void restoreDefaultSettings(){
    preferences.putBool(INITIALIZED, true);
    preferences.putString(TEXT_COLOR, "#FFFFFF");
    preferences.putString(BACKGROUND_COLOR, "#000000");
    preferences.putInt(BRIGHTNESS, 50);
    preferences.putString(CURRENT_MODE, "time");
    preferences.putString(LOCATION, "Jerusalem, Israel");
    preferences.putInt(GMT_OFFSET, 7200);
    preferences.putString(DISPLAYED_STOCKS, "AAPL#TSLA#AMZN#");
    preferences.putInt(STOCKS_SPEED, 100);
    preferences.putString(CYCLE_MODES, "time#weather#stocks#");
    preferences.putInt(CYCLE_SPEED, 100);
}

void SetupPreferences() {
  preferences.begin(MY_METRIC, false);
  if (!preferences.getBool(INITIALIZED, false)) {
    restoreDefaultSettings();
  }
}

void setLocation(String location) {
  preferences.putString(LOCATION, location);
}

String getLocation() {
  return preferences.getString(LOCATION);
}

void setTextColor(String color) {
  preferences.putString(TEXT_COLOR, color);
}

String getTextColor() {
  return preferences.getString(TEXT_COLOR);
}

void setBackgroundColor(String color) {
  Serial.println("inside setBackground color after setting and getting");
  preferences.putString(BACKGROUND_COLOR, color);
  String color1 = preferences.getString(BACKGROUND_COLOR);
  Serial.println(color1);
}

String getBackgroundColor() {
  Serial.print("getting background color: ");
  String color = preferences.getString(BACKGROUND_COLOR);
  Serial.println(color);
  return color;
}

void setDisplayBrightness(int brightness) {
  preferences.putInt(BRIGHTNESS, brightness);
}

int getDisplayBrightness() {
  return preferences.getInt(BRIGHTNESS);
}

void setCurrentMode(String modeName) {
  preferences.putString(CURRENT_MODE, modeName);
}

String getCurrentMode() {
  return preferences.getString(CURRENT_MODE);
}

void setTimeOffsetSetting(int offset) {
  preferences.putInt(GMT_OFFSET, offset);
}

int getTimeOffsetSetting() {
  return preferences.getInt(GMT_OFFSET);
}

void setStocksSpeed(int speed) {
  preferences.putInt(STOCKS_SPEED, speed);
}

int getStocksSpeed() {
  return preferences.getInt(STOCKS_SPEED);
}

void setDisplayedStocks(vector<String> stocks) {
  String enc = encodeStringArr(stocks);
  preferences.putString("ds", enc);
}

void setDisplayedStocks(String stocks) {
  vector<String> dec = decodeStringArr(stocks);
  String enc = encodeStringArr(dec);
  preferences.putString("ds", enc);
}

vector<String> getDisplayedStocks() {
  return decodeStringArr(preferences.getString("ds"));
}

void setCycleSpeed(int speed) {
  preferences.putInt(CYCLE_SPEED, speed);
}

int getCycleSpeed() {
  return preferences.getInt(CYCLE_SPEED);
}

void setCycleModes(vector<String> modes) {
  String enc = encodeStringArr(modes);
  preferences.putString(CYCLE_MODES, enc);
}

void setCycleModes(String modes) {
  vector<String> dec = decodeStringArr(modes);
  String enc = encodeStringArr(dec);
  preferences.putString(CYCLE_MODES, enc);
}

vector<String> getCycleModes() {
  return decodeStringArr(preferences.getString(CYCLE_MODES));
}

String getSettings() {
  DynamicJsonDocument doc(1024);
  doc[TEXT_COLOR] = getTextColor();
  doc[BACKGROUND_COLOR] = getBackgroundColor();
  doc[BRIGHTNESS] = getDisplayBrightness();
  doc[CURRENT_MODE] = getCurrentMode();
  doc[LOCATION] = getLocation();
  doc[GMT_OFFSET] = getTimeOffsetSetting();
  JsonArray disp_stocks = doc.createNestedArray(DISPLAYED_STOCKS);
  for(auto &a: getDisplayedStocks()) {
    disp_stocks.add(a);
  }
  doc[STOCKS_SPEED] = getStocksSpeed();
  JsonArray cycle_modes = doc.createNestedArray(CYCLE_MODES);
  for(auto &a: getCycleModes()) {
    cycle_modes.add(a);
  }
  doc[CYCLE_SPEED] = getCycleSpeed();
  String res;
  serializeJsonPretty(doc, res);
  Serial.print(res);
  return res;
}


void setSetting(String argName, String argVal) {
    if (argVal.length() <= 0) {
        if (DEBUG) {
            Serial.print(PREFERENCES_MANAGER_PREFIX);
            Serial.print(" Arg ");
            Serial.print(argName);
            Serial.println(F(" not set because value is empty"));
        }
        return;
    }
    String message = PREFERENCES_MANAGER_PREFIX;
    if (argName == TEXT_COLOR) {
        setTextColor(argVal);
        message += "Set text color to: ";
        message += argVal;
    } else if (argName == BACKGROUND_COLOR) {
        setBackgroundColor(argVal);
        message += "Set background color to: ";
        message += argVal;
    } else if (argName == BRIGHTNESS) {
        setDisplayBrightness(argVal.toInt());
//        updateBrightness(argVal.toInt()); //TODO
        message += "Set brightness to: ";
        message += argVal;
    } else if (argName == CURRENT_MODE) {
        setCurrentMode(argVal);
        message += "Set current mode to: ";
        message += argVal;
    } else if (argName == LOCATION) {
        setLocation(argVal);
        String a, b, c; // ignore these
//        updateWeatherAndTime(argVal, &a, &b, &c); //TODO
        message += "Set location to: ";
        message += argVal;
    } else if (argName == DISPLAYED_STOCKS) {
        setDisplayedStocks(argVal);
        message += "Set displayed stocks to: ";
        argVal;
        message += argVal;
    } else if (argName == STOCKS_SPEED) {
        setStocksSpeed(argVal.toInt());
        message += "Set stocks speed to: ";
        message += argVal;
    } else if (argName == CYCLE_SPEED) {
        setCycleSpeed(argVal.toInt());
        message += "Set cycle speed to: ";
        message += argVal;
    } else if (argName == CYCLE_MODES) {
        setCycleModes(argVal);
        message += "Set cycle modes to: ";
        message += argVal;
    } else if (argName == PLAIN) {

    } else {
        message = String(PREFERENCES_MANAGER_PREFIX) + "Invalid arg: " + argName;
    }
    if (DEBUG) {
        Serial.println(message);
    }
}

#endif //PREFERENCES_MANAGER_H
