# FINDTracker
This project aims to provide an easy to use interface and implementation for the
Client specifications of the FIND project by Hypercubeplatforms. The project
can be found on [GitHub](https://github.com/schollz/find) and
on the [project page](https://www.internalpositioning.com/). All credit for the
"Framework for Internal Navigation and Discovery" goes to Hypercubeplatforms since
this is only a project that uses the ESP8266 chip as a client for the API provided
by the FIND server.


## Setup
To install this onto your beloved ESP8266 you shall **download and install [PlatformIO](http://platformio.org/)**.
Once you did that successfully you can proceed by downloading this repository by pressing the shiny green button
on the top right. Once downloaded you should connect your ESP8266 to your PC, open up a terminal inside the
downloaded files and run the following commands:
```
platformio run --target upload

SKIP_WEBPACK=true platformio run --target uploadfs
```
Now you shall look onto your WiFi network list and discover your very own `FINDTracker` network. Connect to it
and open up [10.10.10.1/](http://10.10.10.1/) in your browser. It will undoubtly prompt you for a username and
password which by default is set to `admin` and `supersecret` respectively.

## FAQ
#### I do not see it the WiFi network
* When tracking and connected to your network the ESP8266 disables the AP to preserve power
* When tracking and **not** connected it goes into sleep to preserve power as well
* Make sure the ESP8266 is blinking in a regular interval of about 1Hz. 
    * If it is the case then reflash the ESP and try again
    * If that's not the case connect GPIO16 and GND together and reset which disables tracking.
#### I forgot my password
* Connect GPIO14 and GND then reset. It'll restore factory defaults
#### What does the light mean?
There's several different types of signals:
* Blinking
    * **Really fast** (150ms cycle) means it is receiving updates OTA
    * **Slow** (1s cycle) means it is searching for a WiFi network
        * _Note that this only happens when it is not in tracking mode!_
    * **Three times** in a row after it was illuminated means it failed to connect to the network
* Illumination
    * **Constant** means it is in the process of connecting to a WiFi network
    
## Contributing
### Building
Make sure you installed PlatformIO, git, npm and gzip and then run
```
git clone https://github.com/TheMegaTB/FINDTracker.git && cd FINDTracker

## Linux and macOS
./flash.sh

## or in seperated steps
platformio run --target upload
platformio run --target uploadfs

## Sorry windows...you have to wait some more days
```

### PlatformIO
This project relies on [PlatformIO](http://platformio.org/) to manage dependencies,
compile them as well as the projects source and uploading that and the SPIFFS to
the device. In order to effectively use this project it is required that you
install either a standalone version of PlatformIO or download the PIO IDE.
### WebServer
In order to develop the website without the need to upload the SPIFFS on every
change you can run a local webserver (which doesn't feature config loading or writing as well as training)
by executing the following command
```
cd http
./devServer.sh
```

### OTA Serial port
You can connect to the serial monitor of this device by executing the following
command:
```
telnet FINDTracker 23
```

### OTA upload
To upload the C++ or JS code without a USB connection you can run the script provided
by executing the following command:
```
## C++ code
./OTA.sh

## Code in /http (also runs webpack)
./OTA-SPIFFS.sh
```
