#!/usr/bin/env python

boardBlock = """
[env:%%BOARD%%]
platform = espressif8266
board = %%BOARD%%
framework = arduino
extra_script = handleUpload.py
lib_deps =
    ArduinoJson
    ESP8266WebServer
    ESPAsyncTCP
    NTPClient
    WebSockets
"""

def write():
    with open('boards.txt','r') as boards:
        with open('platformio.ini.template') as template:
            with open('platformio.ini','w') as out:
                for line in template:
                    out.write(line)
                for board in boards:
                    board = board.replace('\n', '')
                    print("Processing " + board)
                    out.write(boardBlock.replace("%%BOARD%%", board))

write()
