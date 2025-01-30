
#include <ESPWiFiMqttWrapper.h>

ESPWiFiMqttWrapper wrapper;

const char* MQTT_Server = "192.168.1.9";        // MQTT server address
const char* MQTT_username = "roffisIoBroker";   // MQTT username or API ID
const char* MQTT_password = "thisisnotsecure";  // MQTT password or API secret

const char* WiFi_SSID = "FRITZ1Box Fon WLAN 7360";  // WiFi SSID
const char* WiFi_Password = "wifi-pwd";             // WiFi password
const char* WiFi_HostName = "ESP32-S3-A";           // Host name for this device

const char* MQTT_TOPIC_TMP = "/poc_sys/esp_s3_tmp/tmp";
const char* MQTT_TOPIC_HUM = "/poc_sys/esp_s3_tmp/hum";
const char* MQTT_TOPIC_TMPOS = "/poc_sys/esp_s3_tmp/tmp_os";
const char* MQTT_TOPIC_HUMOS = "/poc_sys/esp_s3_tmp/hum_os";
const char* MQTT_TOPIC_INTERVAL = "/poc_sys/esp_s3_tmp/interval";

unsigned long previousTimestamp = 300000;  // this way all values get send at the start
unsigned int interval = 120000;

void setup() {
  setup_dht();
  setup_sub();

  wrapper.setWiFi(WiFi_HostName, WiFi_SSID, WiFi_Password);
  wrapper.setMqttServer(MQTT_Server, MQTT_username, MQTT_password);
  wrapper.initWiFi();
  wrapper.initMqtt();
}

void loop() {
  wrapper.loop();

  if (millis() - previousTimestamp >= interval) {
    previousTimestamp = millis();
    wrapper.publish(MQTT_TOPIC_TMP, dht_getTmp());
    wrapper.publish(MQTT_TOPIC_HUM, dht_getHum());
  }
}

void setup_sub() {
  wrapper.setSubscription(MQTT_TOPIC_TMPOS, [&](const String message) {
    dht_setTmpOffset(message);
    if (message == "")  // if there was no value set before there will be sent null after subscribing
      wrapper.publish(MQTT_TOPIC_TMPOS, "0.0");
  });

  wrapper.setSubscription(MQTT_TOPIC_HUMOS, [&](const String message) {
    dht_setHumOffset(message);
    if (message == "")
      wrapper.publish(MQTT_TOPIC_HUMOS, "0.0");
  });

  wrapper.setSubscription(MQTT_TOPIC_INTERVAL, [&](const String message) {
    int newInterval = message.toInt();
    if (message == "") {
      wrapper.publish(MQTT_TOPIC_INTERVAL, 120);
    } else if (newInterval < 5) {
      interval = 5000;
      wrapper.publish(MQTT_TOPIC_INTERVAL, 5);
    } else {
      interval = newInterval * 1000;
    }
  });
}
