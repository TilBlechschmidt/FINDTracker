#ifndef DEFAULTS_H
#define DEFAULTS_H

/// -- Things you are supposed to change --
#define RESET_CONF_PIN          14
#define EEPROM_CONF_ADDR        0

#define DEFAULT_WIFI_RECON_INT  60000

#define DEFAULT_HOSTNAME        "FINDTracker"
#define DEFAULT_SSID            "B at Home"
#define DEFAULT_PASSPHRASE      "4898536160015702" // TODO: Put this into a non-git file ;)
#define AP_PASSPHRASE           "12345678"

#define DEFAULT_ACTIVE          false
#define DEFAULT_BUFFER_SIZE     10
#define DEFAULT_TRACKING_URL    "http://10.0.0.38:18003/track"
#define DEFAULT_TRACKING_GROUP  "Family"
#define DEFAULT_TRACKING_USER   "Til"

/// -- Things you are supposed to change --
#define DEBUG           true
// #define BUFFER_SIZE     10

// #define WIFI_RECON_INT  60000
#define HOTSPOT_PIN     0           // Corresponds to D3 on the ESP12E DevKit v2

#define FIND_SERVER_URL "http://192.168.43.25:18003/track"
// #define FIND_SERVER_URL "http://10.0.0.38:18003/track"
#define FIND_GROUP      "Family"
#define FIND_USER       "Til"

// #define SSID            "B at Home"
// #define PASSWORD        "4898536160015702"
// #define SSID            "Droggelbecher"
// #define PASSWORD        "DasBeerBoot2"


/// -- Things you are not supposed to change --
#define LED_PIN 2
#define WIFI_POOLING_INTERVAL 250

#endif // DEFAULTS_H
