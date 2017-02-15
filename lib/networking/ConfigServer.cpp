#include "ConfigServer.hpp"

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
    Serial.println("handleFileRead: " + path);
    if(path.endsWith("/")) path += "index.htm";
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

ConfigServer::ConfigServer(int port) : httpServer(port) {
    ESP8266WebServer* srv = &this->httpServer;
    // srv->on("/inline", [srv](){
    //     if(!srv->authenticate("admin", "supersecret"))
    //         return srv->requestAuthentication();
    //     srv->send(200, "text/plain", "this works as well");
    // });

    srv->on("/reboot", std::bind(&ConfigServer::handleReboot, this));

    srv->onNotFound(std::bind(&ConfigServer::handleNotFound, this));

    SPIFFS.begin();
    srv->begin();
    MDNS.addService("http", "tcp", 80);
}

void ConfigServer::handleReboot() {
    ESP8266WebServer* srv = &this->httpServer;
    if(!srv->authenticate("admin", "supersecret"))
        return srv->requestAuthentication();
    srv->send(200, "text/plain", "{result: 'success'}");
    Terminal::println("Rebooting due to request via HTTP");
    ESP.restart();
}

void ConfigServer::handleNotFound() {
    ESP8266WebServer* srv = &this->httpServer;
    String uri = srv->uri();
    if (uri == "/") uri = INDEX_PAGE_URI;
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
