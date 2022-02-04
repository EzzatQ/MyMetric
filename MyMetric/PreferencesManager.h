#ifndef PREFERENCES_MANAGER_H
#define PREFERENCES_MANAGER_H

#include <vector>

#include <Preferences.h> // https://microcontrollerslab.com/save-data-esp32-flash-permanently-preferences-library/#Preferences.h-Example-1:-Save/Read-key:-value-pairs
#include "Constants.h"
#include "Utils.h"

Preferences preferences;


String getPreferences() {
  String message = "";
  message += String(TEXT_COLOR) + ": " + preferences.getString(TEXT_COLOR, "white") + "\n";
  message += String(BACKGROUND_COLOR) + ": " + preferences.getString(BACKGROUND_COLOR, "black") + "\n";
  message += String(BRIGHTNESS) + ": " + preferences.getInt(BRIGHTNESS, 50) + "\n";
  message += String(CURRENT_MODE) + ": " + preferences.getString(CURRENT_MODE, "time") + "\n";
  message += String(LOCATION) + ": " + preferences.getString(LOCATION, "Jerusalem") + "\n";
  message += String(GMT_OFFSET) + ": " + preferences.getInt(GMT_OFFSET, 7200) + "\n";
  message += String(DISPLAYED_STOCKS) + ": " + preferences.getString(DISPLAYED_STOCKS, "AAPL#TSLA#AMZN#") + "\n";
  message += String(STOCKS_SPEED) + ": " + preferences.getInt(STOCKS_SPEED, 1000) + "\n";
  message += String(CYCLE_MODES) + ": " + preferences.getString(CYCLE_MODES, "time#weather#stocks#") + "\n";
  message += String(CYCLE_SPEED) + ": " + preferences.getInt(CYCLE_SPEED, 1000) + "\n";
  return message;
}


void SetupPreferences() {
  preferences.begin(MY_METRIC, false);
  bool init = preferences.getBool(INITIALIZED, false);
  if (!init) {
    Serial.println("Preferences are not initialized. Setting default settings");
    preferences.putBool(INITIALIZED, true);
    preferences.putString(TEXT_COLOR, "white");
    preferences.putString(BACKGROUND_COLOR, "black");
    preferences.putInt(BRIGHTNESS, 50);
    preferences.putString(CURRENT_MODE, "time");
    preferences.putString(LOCATION, "Jerusalem");
    preferences.putInt(GMT_OFFSET, 7200);
    preferences.putString(DISPLAYED_STOCKS, "[AAPL, TSLA, AMZN]");
    preferences.putInt(STOCKS_SPEED, 1000);
    preferences.putString(CYCLE_MODES, "[time, weather, stocks]");
    preferences.putInt(CYCLE_SPEED, 1000);
  } else {
    Serial.println("Preferences are defined:");
  }
}

void setLocation(String location) {
  preferences.putString(LOCATION, location);
}

String getLocation() {
  return preferences.getString(LOCATION, "Jerusalem");
}

void setTextColor(String color) {
  preferences.putString(TEXT_COLOR, color);
}

String getTextColor() {
  return preferences.getString(TEXT_COLOR, "white");
}

void setBackgroundColor(String color) {
  preferences.putString(BACKGROUND_COLOR, color);
}

String getBackgroundColor() {
  return preferences.getString(BACKGROUND_COLOR, "black");
}

void setDisplayBrightness(int brightness) {
  preferences.putInt(BRIGHTNESS, brightness);
}

int getDisplayBrightness() {
  return preferences.getInt(BRIGHTNESS, 50);
}

void setCurrentMode(String modeName) {
  preferences.putString(CURRENT_MODE, modeName);
}

String getCurrentMode() {
  return preferences.getString(CURRENT_MODE, "time");
}

void setTimeOffsetSetting(int offset) {
  preferences.putInt(GMT_OFFSET, offset);
}

int getTimeOffsetSetting() {
  return preferences.getInt(GMT_OFFSET, 7200);
}

void setStocksSpeed(int speed) {
  preferences.putInt(STOCKS_SPEED, speed);
}

int getStocksSpeed() {
  return preferences.getInt(STOCKS_SPEED, 1000);
}

void setDisplayedStocks(vector<String> stocks) {
  String enc = encodeStringArr(stocks);
  preferences.putString(DISPLAYED_STOCKS, enc);
}

vector<String> getDisplayedStocks() {
  return decodeStringArr(preferences.getString(DISPLAYED_STOCKS, "AAPL#TSLA#AMZN#"));
}

void setCycleSpeed(int speed) {
  preferences.putInt(CYCLE_SPEED, speed);
}

int getCycleSpeed() {
  return preferences.getInt(CYCLE_SPEED, 1000);
}

void setCycleModes(vector<String> modes) {
  String enc = encodeStringArr(modes);
  preferences.putString(CYCLE_MODES, enc);
}

vector<String> getCycleModes() {
  return decodeStringArr(preferences.getString(CYCLE_MODES, "time#weather#stocks#"));
}

#endif //PREFERENCES_MANAGER_H
