#ifndef DEFAULTS_H
#define DEFAULTS_H

/// -- Things you are supposed to change --
#define RESET_CONF_PIN          14  // D5 on nodemcuv2
#define DISABLE_TRACKING_PIN    12  // D6 on nodemcuv2
#define EEPROM_CONF_ADDR        0

#define DEFAULT_WIFI_RECON_INT  60000

#define DEFAULT_HOSTNAME        "FINDTracker"
#define DEFAULT_SSID            "YourWiFi"
#define DEFAULT_PASSPHRASE      "supersecret"
#define DEFAULT_AUTH            "supersecret"

#define DEFAULT_ACTIVE          false
#define DEFAULT_BUFFER_SIZE     3
#define DEFAULT_TRACKING_HOST   "ml.internalpositioning.com"

#define DEBUG

/// -- Things you are not supposed to change --
#define LED_PIN 2
#define WIFI_POOLING_INTERVAL 250

#endif // DEFAULTS_H
