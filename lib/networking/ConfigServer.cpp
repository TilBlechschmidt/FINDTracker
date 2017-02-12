#include "ConfigServer.hpp"

ConfigServer::ConfigServer(int port) : httpServer(port) {
    ESP8266WebServer* srv = &this->httpServer;
    srv->on("/inline", [srv](){
        srv->send(200, "text/plain", "this works as well");
    });

    // srv->onNotFound(this->handleNotFound);
    srv->onNotFound(std::bind(&ConfigServer::handleNotFound, this));

    srv->begin();
    MDNS.addService("http", "tcp", 80);
}

void ConfigServer::handleNotFound() {
    ESP8266WebServer* srv = &this->httpServer;
    String message = "File Not Found\n\n";
    message += "URI: ";
    message += srv->uri();
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

void ConfigServer::handle() {
    this->httpServer.handleClient();
}
