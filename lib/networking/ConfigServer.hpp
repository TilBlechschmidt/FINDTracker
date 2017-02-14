#ifndef CONFIG_SERVER_H
#define CONFIG_SERVER_H

#include <helpers.hpp>

#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <FS.h>

#define INDEX_PAGE_URI "/index.html"

class ConfigServer {
    ESP8266WebServer httpServer;

    void handleNotFound();
    bool handleFileRead(String path);

    String getContentType(String filename);
public:
    ConfigServer(int port);

    void handle();
};

#endif // CONFIG_SERVER_H
