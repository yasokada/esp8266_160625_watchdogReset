#include <ESP8266WiFi.h>
#include <WiFiUDP.h>

/*
 * This program may cause watchdog reset even after being overwritten by other EPS8266 program
 * 
 * Environment: Arduino 1.6.6
 * ESP-WROOM-02
 */

/*
 * v0.2 2016 Jun. 25
 *   - disconnect WiFi when WiFi connection failed
 *   - modify WiFi_setup() to avoid endless while loop
 * v0.1 2016 Jun. 25
 *   - add WiFi_setup()
 */

static WiFiUDP wifiUdp;
static const int kPortUdp_logger = 7000;

static const char *kWifiSsid = "esp8266";
static const char *kWifiPass = "12345678";

static const char *kLoggerIP = "192.168.79.2";
static bool s_isWiFiConnected = false;

/*
 * in WiFi_setup(), changing "#if 1" to "#if 0" will cause watchdog reset
 */

void WiFi_setup()
{
  bool bfOk = false;
  WiFi.begin(kWifiSsid, kWifiPass);
#if 1
  for(int loop = 0; loop < 3; loop++) {
    if (WiFi.status() == WL_CONNECTED) {
      s_isWiFiConnected = true;
      break;
    }
    delay(500); // msec
  }
  if (s_isWiFiConnected) {
    wifiUdp.begin(kPortUdp_logger);  
  } else {
    WiFi.disconnect();
  }
#else
  while ( WiFi.status() != WL_CONNECTED) {
    delay(500); // msec  
  }
  wifiUdp.begin(kPortUdp_logger);
#endif  
}

void setup() {
  Serial.begin(115200);
  Serial.println("");

  WiFi_setup(); 
}

void loop() {

}
