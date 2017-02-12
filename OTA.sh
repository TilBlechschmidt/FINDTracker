HOSTNAME='FINDTracker'
IP=$(getent hosts "${HOSTNAME}" | awk '{ print $1 }')
platformio run --silent --target upload --upload-port ${IP}
