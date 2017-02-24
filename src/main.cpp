#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <DNSServer.h>
#include <Ticker.h>

#include "helpers.hpp"
#include "defaults.hpp"
#include "radio.hpp"
#include "Config.hpp"
#include "TrackingData.hpp"
#include "ConfigServer.hpp"

#define DNS_PORT 53

Ticker wifiBlinker;

Config* conf = new Config();
Radio rf(conf);
TrackingData data(conf, DEFAULT_BUFFER_SIZE);
ConfigServer cfgSrv(conf, 80);

WebSocketsServer webSocket(81);
DNSServer dnsServer;
IPAddress localIP(10, 10, 10, 1);

void setup () {
    // Set up the EEPROM w/ a maximum size of 4096 bytes
    EEPROM.begin(4096);

    /// Set up the built-in LED and turn it on to let the user know the ESP is working
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);

    /// Open up the serial and TCP monitor
    Terminal::begin(115200);

    // Print some stats
    Terminal::printf("CPU running at %dMHz, Cycle %d, Flash chip running at %d MHz, VCC is at %d\n", ESP.getCpuFreqMHz(), ESP.getCycleCount(), ESP.getFlashChipSpeed()/1000000, ESP.getVcc());

    // If the pin is not pulled to ground read config or write the default one if its not
    if (digitalRead(RESET_CONF_PIN)) {
        conf->read(EEPROM_CONF_ADDR);
    } else {
        Terminal::println("Restoring factory settings...");
        conf->write(EEPROM_CONF_ADDR);
    }

    // If the pin is pulled to ground then disable tracking
    if (!digitalRead(DISABLE_TRACKING_PIN)) {
        Terminal::println("Disabling tracking...");
        conf->readFromString("{'active': false}");
        conf->write(EEPROM_CONF_ADDR);
    }

    // Set the hostname
    WiFi.hostname("FINDTracker");

    // Setup the radios according to the configuration
    rf.setup();

    MDNS.begin("FINDTracker");
    MDNS.addService("http", "tcp", 80);

    // Setup the OTA server
    OTA();

    // Setup the websocket server
    webSocket.begin();

    // Setup the DNS server
    dnsServer.setTTL(300);
    dnsServer.setErrorReplyCode(DNSReplyCode::ServerFailure);
    dnsServer.start(DNS_PORT, "findtracker", localIP);
}

void runServerHandlers() {
    ArduinoOTA.handle();
    cfgSrv.handle();
    Terminal::handle();
    webSocket.loop();
    dnsServer.processNextRequest();
}

int lastWatchdog = -999999;
int sleepTimeMS;
int lastScan = -999999;
int lastUpdate = -999999;
bool connected;
bool active;
void loop() {
    if (millis() - lastUpdate > 1500) {
        connected = rf.connected();
        active = conf->get<bool>("active");
        lastUpdate = millis();
    }

    // Check for a WiFi connection and attempt to reestablish it if it died
    if (
        (active && !connected) ||
        (!active && !connected && millis() - lastScan > 30000)
    ) {
        digitalWrite(LED_PIN, LOW);
        if (!rf.connect()) {
            Terminal::print("Connection failed. ");
            if (active) {
                // Enter deep sleep in case the connection failed
                sleepTimeMS = conf->get<int>("wifiReconnectionInterval");
                blink(); blink(); blink();
                Terminal::printf("Entering deep sleep mode for %dms ...\n", sleepTimeMS);
                ESP.deepSleep(sleepTimeMS * 1000, WAKE_NO_RFCAL);
            } else {
                Terminal::println("");
                wifiBlinker.attach(0.5, blinkSync);
            }
        } else {
            wifiBlinker.detach();
            digitalWrite(LED_PIN, HIGH);
        }
        lastScan = millis();
    }

    // TODO: The data.send() step takes way too long
    if (active) {
        /// Update the environment data (scan for networks)
        if (data.update()) {
            // Send the data to the FIND Server
            String response = data.send();

            /// Blink to indicate that we have sent our location
            if (response != "") {
                blink();
                webSocket.broadcastTXT(response);
            }
        }

        // Enter a very basic sleep mode and limit the amount of cycles to preserve power
        // (Turn off the radio and wake it up periodically to answer beacon signals from router)
        // TODO Only do this when nothing else is connected (low power mode setting maybe?)
        //      since it breaks all kind of things like websockets, HTTP etc.
        WiFi.setSleepMode(WIFI_MODEM_SLEEP);
        delay(500);
    } else {
        /// Let some background tasks run
        delay(100);
        yield();
    }

    /// Run all kinds of server handlers
    runServerHandlers();

    // Send a watchdog signal for all websocket clients
    if (millis() - lastWatchdog > 5000) {
        webSocket.broadcastTXT("watchdog");
        lastWatchdog = millis();
    }
}
