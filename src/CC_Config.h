#pragma once

#define __DEVICE_NAME__ "BaseProject"
#define __DEVICE_VERSION__ "0.1"

#define NETWORK_WAIT_TIME_PER_TRY 10 //seconds
#define NETWORK_TRY_TIMES 3

#define WIFI_PREFERENCES_FILENAME "wifi"
#define WIFI_PREFERENCES_SSID_KEY "ssid"
#define WIFI_PREFERENCES_PASWORD_KEY "password"
#define MQTT_BROKER_PREFERENCES_FILENAME "mqtt"
#define MQTT_BROKER_PREFERENCES_ADDRESS "mqttAddress"



#define STACK_SIZE (ESP_TASK_MAIN_STACK) // Stack size for each new thread

#define WEB_SERVER_PRIORITY 1
#define OTA_PRIORITY 1

#define WEBSERVER_CORE	0
#define OTA_CORE	0
