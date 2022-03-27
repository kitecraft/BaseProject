#pragma once
#include <Arduino.h>
#include "PreferencesManager.h"
#include "../CC_Config.h"
#include <Preferences.h>

static String GetSsid()
{
    String ret;
    Preferences preferences;
    preferences.begin(WIFI_PREFERENCES_FILENAME, false);
    ret = preferences.getString(WIFI_PREFERENCES_SSID_KEY, "");
    preferences.end();
    return ret;
}

static void SetSsid(String s)
{
    Preferences preferences;
    preferences.begin(WIFI_PREFERENCES_FILENAME, false);
    preferences.putString(WIFI_PREFERENCES_SSID_KEY, s);
    preferences.end();
}

static String GetSsidPassword()
{
    String ret;
    Preferences preferences;
    preferences.begin(WIFI_PREFERENCES_FILENAME, false);
    ret = preferences.getString(WIFI_PREFERENCES_PASWORD_KEY, "");
    preferences.end();

    return ret;
}

static void SetSsidPassword(String s)
{
    Preferences preferences;
    preferences.begin(WIFI_PREFERENCES_FILENAME, false);
    preferences.putString(WIFI_PREFERENCES_PASWORD_KEY, s);
    preferences.end();
}

static String GetMqttBrokerAddress()
{
    String ret;
    Preferences preferences;
    preferences.begin(MQTT_BROKER_PREFERENCES_FILENAME, false);
    ret = preferences.getString(MQTT_BROKER_PREFERENCES_ADDRESS, "");
    preferences.end();

    return ret;
}

static void SetMqttBrokerAddress(String s)
{
    Preferences preferences;
    preferences.begin(MQTT_BROKER_PREFERENCES_FILENAME, false);
    preferences.putString(MQTT_BROKER_PREFERENCES_ADDRESS, s);
    preferences.end();
}
