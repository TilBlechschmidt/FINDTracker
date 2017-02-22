# FINDTracker
This project aims to provide an easy to use interface and implementation of the
Client specifications of the FIND project by Hypercubeplatforms. The project
can be found on [GitHub](https://github.com/schollz/find) and
on the [project page](https://www.internalpositioning.com/). All credit for the
"Framework for Internal Navigation and Discovery" goes to Hypercubeplatforms since
this is only a project that uses the ESP8266 chip as a client for the API provided
by the FIND server.

## Usage

## Flashing
Mdake sure you installed PlatformIO, git, npm and gzip and then run 
```
git clone https://github.com/TheMegaTB/FINDTracker.git

## Linux and macOS
./flash.sh

## Windows
platformio run --target upload
platformio run --target uploadfs
```

## Development
### PlatformIO
This project relies on [PlatformIO](http://platformio.org/) to manage dependencies,
compile them as well as the projects source and uploading that and the SPIFFS to
the device. In order to effectively use this project it is required that you
install either a standalone version of PlatformIO or download the PIO IDE.
### WebServer
In order to develop the website without the need to upload the SPIFFS on every
change you can run a local webserver (which doesn't feature config loading or writing)
by executing the following command
```
cd http
./devServer.sh
```

### OTA Serial port
You can connect to the serial monitor of this device by executing the following
command
```
telnet FINDTracker 23
```

### OTA upload
To upload the C++ code without a USB connection you can run the script provided
by executing the following command
```
## C++ code
./OTA.sh

## Code in /http (also runs webpack)
./OTA-SPIFFS.sh
```
