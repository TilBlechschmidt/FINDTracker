# FINDTracker
This project aims to provide an easy to use interface and implementation of the
Client specifications of the FIND project by Hypercubeplatforms. The project
can be found on [GitHub](https://github.com/schollz/find) and
on the [project page](https://www.internalpositioning.com/). All credit for the
"Framework for Internal Navigation and Discovery" goes to Hypercubeplatforms since
this is only a project that uses the ESP8266 chip as a client for the API provided
by the FIND server.

## Default authentication
The default username is `admin` and the default password is `supersecret`

## Usage
Once installed you should check your WiFi networks. There should be a `FINDTracker<number>` network where `<number>` is the unique ID of your chip. Join that network, open your browser and visit [findtracker/](http://findtracker/). You should now (after a brief loading period which depends on your proximity to the chip and might vary between 3s and 60s) see the welcome screen of your very own tracker!

First thing you should change are the WiFi settings under the WiFi tab at the top to match your personal network at home. After that you should set up your tracking server, group and user (which defaults to ml.internalpositioning.com, the ID of your chip and *again* the ID). Finally you can start training some locations in the learning tab and then hit the big slider at the top right to start tracking!

### Disabling tracking
When you enabled tracking the ESP deactivates the configuration AP to preserve power. This renders it inaccessible in case you misconfigured the WiFi settings.
To fix this you can simply connect GPIO 12 (D6 on the NodeMCUv2) to ground and reset the ESP to disable tracking.

### Resetting the configuration
If for some reason you cannot access your tracker anymore you can reset the configuration by pulling GPIO 14 (D5 on the NodeMCUv2) to ground and resetting the ESP.

## Installation

### Flashing the binary blobs
Okay so in case you trust me that I haven't uploaded some evil binary blobs and you actually know how to flash binary blobs onto the ESP8266 then you can download the current ones (program and SPIFFS blobs) from the release page and flash them yourself (haven't figured it out myself yet as I only use PIO, see below  for details).

### Building on your own
Make sure you installed PlatformIO, git, npm and gzip and then run
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
