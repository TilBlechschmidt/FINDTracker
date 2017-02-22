#!/bin/sh

if ! type "npm" > /dev/null; then
    echo "[ERROR] npm is not installed! Please do that first and then run this again."
fi

if ! type "platformio" > /dev/null; then
    echo "[ERROR] PlatformIO is not installed! Please install it first and then run this again."
fi

echo "Flashing server software ..."
platformio run --target upload -s
echo "Downloading, building and flashing server assets (this might take a moment) ..."
platformio run --target uploadfs -s
echo "Done!"
echo "Connect to the WiFi Network 'FINDTracker' and visit http://findtracker/ in your browser of trust to start configuration."
