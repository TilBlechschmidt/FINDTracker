#ifndef CONFIG_SERVER_H
#define CONFIG_SERVER_H

#include <helpers.hpp>

#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <FS.h>

#include "Config.hpp"

#define INDEX_FILE_NAME "index.html"

class ConfigServer {
    ESP8266WebServer httpServer;
    Config* cfg;

    void requirePermission();

    void handleNotFound();
    void handleReboot();
    bool handleFileRead(String path);

    void handleConfigGet();
    void handleConfigPost();

    String getContentType(String filename);
public:
    ConfigServer(Config* conf, int port);

    void handle();
};

#endif // CONFIG_SERVER_H
