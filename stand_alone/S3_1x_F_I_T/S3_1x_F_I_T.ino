
#include <ESPWiFiMqttWrapper.h>

ESPWiFiMqttWrapper wrapper;

const char* MQTT_Server = "192.168.1.9";        // MQTT server address
const char* MQTT_username = "roffisIoBroker";   // MQTT username or API ID
const char* MQTT_password = "thisisnotsecure";  // MQTT password or API secret

const char* WiFi_SSID = "FRITZ1Box Fon WLAN 7360";  // WiFi SSID
const char* WiFi_Password = "wifi-pwd";             // WiFi password
const char* WiFi_HostName = "ESP32-S3-A";           // Host name for this device

const char* MQTT_TOPIC_POWER = "/poc_sys/esp_s3_fit/power";
const char* MQTT_TOPIC_BUTTON = "/poc_sys/esp_s3_fit/button";
const char* MQTT_TOPIC_LED = "/poc_sys/esp_s3_fit/led";

unsigned long previousTimestamp = 0;

void setup() {
  setup_socket();
  setup_sub();

  wrapper.setWiFi(WiFi_HostName, WiFi_SSID, WiFi_Password);
  wrapper.setMqttServer(MQTT_Server, MQTT_username, MQTT_password);
  wrapper.initWiFi();
  wrapper.initMqtt();
}

void loop() {
  wrapper.loop();

  if (millis() - previousTimestamp >= 50) {  // waiting between checks helps with debouncing
    previousTimestamp = millis();
    if (getButtonChanged()) {
      if (getButtonState())
        wrapper.publish(MQTT_TOPIC_BUTTON, "true");
      else
        wrapper.publish(MQTT_TOPIC_BUTTON, "false");
    }
  }
}

void setup_sub() {
  wrapper.setSubscription(MQTT_TOPIC_POWER, [&](const String message) {
    setPower(message);
    if (message == "") {  // if there was no value set before there will be sent null after subscribing
      wrapper.publish(MQTT_TOPIC_POWER, "false");
    }
  });

  wrapper.setSubscription(MQTT_TOPIC_LED, [&](const String message) {
    setLedMode(message);
    if (message == "") {
      wrapper.publish(MQTT_TOPIC_LED, "Sync");
    }
  });
}
