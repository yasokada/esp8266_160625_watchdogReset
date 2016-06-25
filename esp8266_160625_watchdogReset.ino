#include <ESP8266WiFi.h>
#include <WiFiUDP.h>


static WiFiUDP wifiUdp;
static const int kPortUdp_logger = 7000;

static const char *kWifiSsid = "esp8266";
static const char *kWifiPass = "12345678";

static const char *kLoggerIP = "192.168.79.2";

void WiFi_setup()
{
  WiFi.begin(kWifiSsid, kWifiPass);
  while ( WiFi.status() != WL_CONNECTED) {
    delay(500); // msec  
  }
  wifiUdp.begin(kPortUdp_logger);
}

void setup() {
  Serial.begin(115200);
  Serial.println("");

  WiFi_setup(); 
}

void loop() {

}
