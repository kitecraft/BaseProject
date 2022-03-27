#pragma once
#include <Arduino.h>
#include "FS.h"
#include "SPIFFS.h"

static String IceFS_ReadFile(String filename)
{
	SPIFFS.begin(false);
	String ret = "";

	File file = SPIFFS.open(filename);
	if (!file) {
		Serial.print("Failed to open file: ");
		Serial.println(filename);
		return ret;
	}

	while (file.available()) {
		ret += file.readString();
	}
	file.close();
	return ret;
}

