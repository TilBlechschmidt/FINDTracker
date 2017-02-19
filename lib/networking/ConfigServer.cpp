#include "ConfigServer.hpp"

void ConfigServer::requirePermission() {
    ESP8266WebServer* srv = &this->httpServer;
    if(!srv->authenticate("admin", this->cfg->get<String>("auth").c_str()))
        return srv->requestAuthentication();
}

String ConfigServer::getContentType(String filename) {
    if(this->httpServer.hasArg("download")) return "application/octet-stream";
    else if(filename.endsWith(".htm")) return "text/html";
    else if(filename.endsWith(".html")) return "text/html";
    else if(filename.endsWith(".css")) return "text/css";
    else if(filename.endsWith(".js")) return "application/javascript";
    else if(filename.endsWith(".png")) return "image/png";
    else if(filename.endsWith(".gif")) return "image/gif";
    else if(filename.endsWith(".jpg")) return "image/jpeg";
    else if(filename.endsWith(".ico")) return "image/x-icon";
    else if(filename.endsWith(".xml")) return "text/xml";
    else if(filename.endsWith(".pdf")) return "application/x-pdf";
    else if(filename.endsWith(".zip")) return "application/x-zip";
    else if(filename.endsWith(".gz")) return "application/x-gzip";
    return "text/plain";
}

bool ConfigServer::handleFileRead(String path) {
    Terminal::println("handleFileRead: " + path);
    if(path.endsWith("/")) path += INDEX_FILE_NAME;
    String contentType = getContentType(path);
    String pathWithGz = path + ".gz";
    if(SPIFFS.exists(pathWithGz) || SPIFFS.exists(path)) {
    if(SPIFFS.exists(pathWithGz))
            path += ".gz";
        File file = SPIFFS.open(path, "r");
        size_t sent = this->httpServer.streamFile(file, contentType);
        file.close();
        return true;
    }
    return false;
}

void ConfigServer::handleConfigGet() {
    this->requirePermission();

    String config;
    this->cfg->data.printTo(config);
    this->httpServer.send(200, "application/json", config);
}

void ConfigServer::handleConfigPost() {
    this->requirePermission();

    ESP8266WebServer* srv = &this->httpServer;
    this->cfg->readFromString(srv->arg("plain"));
    this->cfg->write(EEPROM_CONF_ADDR);
    srv->send(200, "application/json", "{result: 'success'}");
}

void ConfigServer::handleReboot() {
    this->requirePermission();

    this->httpServer.send(200, "text/plain", "{result: 'success'}");
    Terminal::println("Rebooting due to request via HTTP");
    ESP.restart();
}

void ConfigServer::handleScan() {
    TrackingData td(this->cfg, DEFAULT_BUFFER_SIZE);
    bool success = false;
    for (int i = DEFAULT_BUFFER_SIZE; i > 0; i--) {
        while (!success) {
            success = td.update();
            delay(200);
        }
        success = false;
    }
    String environment = td.assemble();
    this->httpServer.send(200, "application/json", environment);
}

ConfigServer::ConfigServer(Config* conf, int port) : httpServer(port), cfg(conf) {
    ESP8266WebServer* srv = &this->httpServer;

    srv->on("/reboot", std::bind(&ConfigServer::handleReboot, this));

    srv->on("/config", HTTP_GET, std::bind(&ConfigServer::handleConfigGet, this));
    srv->on("/config", HTTP_POST, std::bind(&ConfigServer::handleConfigPost, this));

    srv->on("/scan", HTTP_GET, std::bind(&ConfigServer::handleScan, this));

    srv->onNotFound(std::bind(&ConfigServer::handleNotFound, this));

    SPIFFS.begin();
    srv->begin();
    MDNS.addService("http", "tcp", 80);
}

void ConfigServer::handleNotFound() {
    ESP8266WebServer* srv = &this->httpServer;
    String uri = srv->uri();
    if (!handleFileRead(uri)) {
        String message = "File Not Found\n\n";
        message += "URI: ";
        message += uri;
        message += "\nMethod: ";
        message += (srv->method() == HTTP_GET)?"GET":"POST";
        message += "\nArguments: ";
        message += srv->args();
        message += "\n";
        for (uint8_t i = 0; i < srv->args(); i++){
            message += " " + srv->argName(i) + ": " + srv->arg(i) + "\n";
        }
        srv->send(404, "text/plain", message);
    }
}

void ConfigServer::handle() {
    this->httpServer.handleClient();
}
