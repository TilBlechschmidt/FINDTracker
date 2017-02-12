HOSTNAME='FINDTracker'
IP=$(getent hosts "${HOSTNAME}" | awk '{ print $1 }')
platformio run --target upload --upload-port ${IP}
