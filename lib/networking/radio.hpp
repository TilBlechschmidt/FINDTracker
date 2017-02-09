#ifndef NETWORKING_H
#define NETWORKING_H

#include "Config.hpp"

class Radio {
    Config configuration;

public:
    bool connect();
};

#endif // NETWORKING_H
