#include "helpers.hpp"

void blink() {
    digitalWrite(LED_PIN, LOW);
    delay(75);
    digitalWrite(LED_PIN, HIGH);
    delay(75);
}

uint8_t ledStatus;
void blinkSync() {
    if (ledStatus)
        digitalWrite(LED_PIN, HIGH);
    else
        digitalWrite(LED_PIN, LOW);
    ledStatus = (ledStatus + 1) % 2; // Flip ledStatus

}

Ticker blinker; // Ticker object called blinker.

void OTA() {
    // Port defaults to 8266
    // ArduinoOTA.setPort(8266);

    // Hostname defaults to esp8266-[ChipID]
    // ArduinoOTA.setHostname("myesp8266");

    // No authentication by default
    ArduinoOTA.setPassword("supersecret");

    // Password can be set with it's md5 value as well
    // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
    // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

    ArduinoOTA.onStart([]() {
        String type;
        // if (ArduinoOTA.getCommand() == U_FLASH)
            type = "sketch";
        // else // U_SPIFFS
            // type = "filesystem";

        // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
        Terminal::println("Start updating " + type);
        blinker.attach(0.1, blinkSync);
    });
    ArduinoOTA.onEnd([]() {
        blinker.detach();
        Terminal::println("\nEnd");
    });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        Terminal::printf("Progress: %u%%\r", (progress / (total / 100)));
    });
    ArduinoOTA.onError([](ota_error_t error) {
        blinker.detach();
        Terminal::printf("Error[%u]: ", error);
        if (error == OTA_AUTH_ERROR) Terminal::println("Auth Failed");
        else if (error == OTA_BEGIN_ERROR) Terminal::println("Begin Failed");
        else if (error == OTA_CONNECT_ERROR) Terminal::println("Connect Failed");
        else if (error == OTA_RECEIVE_ERROR) Terminal::println("Receive Failed");
        else if (error == OTA_END_ERROR) Terminal::println("End Failed");
    });
    ArduinoOTA.begin();
}

namespace Terminal {
    WiFiServer server(23);
    WiFiClient clients[MAX_SRV_CLIENTS];
    uint8_t i;

    void begin(int baudrate) {
        Serial.begin(baudrate);
        Serial.println();

        server.begin();
        server.setNoDelay(true);
    }

    void handle() {
        // Check if there are any new clients
        if (server.hasClient()) {
            for(i = 0; i < MAX_SRV_CLIENTS; i++){
                //find free/disconnected spot
                if (!clients[i] || !clients[i].connected()) {
                  if(clients[i]) clients[i].stop();
                  clients[i] = server.available();
                //   Serial.print("New client: "); Serial.print(i);
                  continue;
                }
            }
            //no free/disconnected spot so reject
            WiFiClient serverClient = server.available();
            serverClient.stop();
        }
    }

    void print(char* str, int len) {
        Serial.print(str);

        //push UART data to all connected telnet clients
        for (i = 0; i < MAX_SRV_CLIENTS; i++){
            if (clients[i] && clients[i].connected()) {
                clients[i].write((const uint8_t*) str, len);
                delay(1);
            }
        }
    }

    void print(String str) {
        Terminal::print((char*) str.c_str(), str.length());
    }

    void println(char* str, int len) {
        strcat(str, "\n");
        Terminal::print(str, len+1);
    }

    void println(String str) {
        Terminal::println((char*) str.c_str(), str.length());
    }

    void printf(char* str, ...) {
    	char* buf;
        int len = 0;
    	va_list args;

    	va_start(args, str);
    	vasprintf(&buf, str, args, &len);
    	va_end(args);

        Terminal::print(buf, len);
    }

    void printf(String str, ...) {
        char* buf;
        int len = 0;
        va_list args;

        va_start(args, str);
        vasprintf(&buf, (char*) str.c_str(), args, &len);
        va_end(args);

        Terminal::print(buf, len);
    }
}

int vasprintf(char** strp, const char* fmt, va_list ap, int* size) {
    va_list ap2;
    va_copy(ap2, ap);
    char tmp[1];
    *size = vsnprintf(tmp, 1, fmt, ap2);
    if (*size <= 0) return *size;
    va_end(ap2);
    *size += 1;
    *strp = (char*)malloc(*size * sizeof(char));
    return vsnprintf(*strp, *size, fmt, ap);
}
