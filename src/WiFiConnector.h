#include <Arduino.h>
#include <functional>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Ticker.h>
// #define nullptr NULL
//#define WIFI_DEBUG_MODE
using namespace std;

#ifdef ESP8266
extern "C" {
  #include "user_interface.h"
}
#endif

#ifdef WIFI_DEBUG_MODE
    #define WIFI_DEBUG_PRINTER Serial
    #define WIFI_DEBUG_PRINT(...) { WIFI_DEBUG_PRINTER.print(__VA_ARGS__); }
    #define WIFI_DEBUG_PRINTLN(...) { WIFI_DEBUG_PRINTER.println(__VA_ARGS__); }
#else
    #define WIFI_DEBUG_PRINT(...) { }
    #define WIFI_DEBUG_PRINTLN(...) { }
#endif

// TYPES
// typedef enum {
//     WL_NO_SHIELD        = 255,   // for compatibility with WiFi Shield library
//     WL_IDLE_STATUS      = 0,
//     WL_NO_SSID_AVAIL    = 1,
//     WL_SCAN_COMPLETED   = 2,
//     WL_CONNECTED        = 3,
//     WL_CONNECT_FAILED   = 4,
//     WL_CONNECTION_LOST  = 5,
//     WL_DISCONNECTED     = 6
// } wl_status_t;


class WiFiConnector {
  private:
    String _ssid;
    String _passphase;
    WiFiConnector* s_instance;
    bool _initialised = false;
  protected:
    WiFiConnector() { };
public:
    typedef std::function<void(const void*)> wifi_callback_t;
    uint32_t counter = 0;
    WiFiConnector(String, String);
    ~WiFiConnector(){
      delete s_instance;
    };

    void setSsid(String);
    void setPasspharse(String);

    static WiFiConnector* instance()
    {
      static WiFiConnector *s_instance = NULL;
      // Serial.println(s_instance, HEX);
      Serial.printf("addr: %x\r\n", s_instance);
      if (!s_instance)
        s_instance = new WiFiConnector;
      Serial.printf("addr: %x\r\n", s_instance);
      return s_instance;
    }

    void init();
    void loop();

};

// WiFiConnector* WiFiConnector::s_instance = NULL;
