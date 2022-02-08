#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "SPIFFS.h"
#include "Constants.h"

bool FILE_DEBUG = 0;

void SetupFileManager() {
    if (!SPIFFS.begin()) {
        if (FILE_DEBUG) {
            Serial.print(FILE_MANAGER_PREFIX);
            Serial.println("SPIFFS mount failed");
        }
        return;
    }
    if (FILE_DEBUG) {
        Serial.print(FILE_MANAGER_PREFIX);
        Serial.println("SPIFFS mounted");
    }
}

void formatFS() {
    if (FILE_DEBUG) {
        Serial.print(FILE_MANAGER_PREFIX);
        Serial.println("Formatting SPIFFS filesystem");
    }
    SPIFFS.format();
}


//String listDir(String dirname) {
//    String message;
//    message = String(FILE_MANAGER_PREFIX) + "Listing directory: " + dirname + "\n";
//
//    Dir root = SPIFFS.openDir(dirname);
//
//    while (root.next()) {
//        File file = root.openFile("r");
//        message += "  FILE: ";
//        message += root.fileName();
//        message += "  SIZE: ";
//        message += file.size();
//        time_t cr = file.getCreationTime();
//        time_t lw = file.getLastWrite();
//        file.close();
//    }
//    if (FILE_DEBUG) {
//        Serial.println(message);
//    }
//    return message;
//}


String readFile(String path) {
    Serial.print(FILE_MANAGER_PREFIX);
    Serial.print("Reading file: ");
    Serial.println(path);

    File file = SPIFFS.open(path, "r");
    if (!file) {
        Serial.print(FILE_MANAGER_PREFIX);
        Serial.println("Failed to open file for reading");
        return "";
    }
    String toReturn = file.readString();
    file.close();
    return toReturn;
}

bool writeFile(String path, String message) {
    Serial.print(FILE_MANAGER_PREFIX);
    Serial.print("Writing file: ");
    Serial.println(path);

    bool success = false;
    File file = SPIFFS.open(path, "w");
    if (!file) {
        Serial.print(FILE_MANAGER_PREFIX);
        Serial.println("Failed to open file for writing");
        return false;
    }
    if (file.print(message)) {
        Serial.print(FILE_MANAGER_PREFIX);
        Serial.println("File written");
        success = true;
    } else {
        Serial.print(FILE_MANAGER_PREFIX);
        Serial.println("Write failed");
        success = false;
    }
    delay(2000);
    file.close();
    return success;
}

#endif //FILE_MANAGER_H
