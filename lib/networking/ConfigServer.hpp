#ifndef CONFIG_SERVER_H
#define CONFIG_SERVER_H

#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

class ConfigServer {
    ESP8266WebServer httpServer;

    void handleNotFound();
public:
    ConfigServer(int port);

    void handle();
};

#endif // CONFIG_SERVER_H
