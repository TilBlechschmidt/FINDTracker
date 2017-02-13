HOSTNAME='FINDTracker'
IP=$(getent hosts "${HOSTNAME}" | awk '{ print $1 }')
PLATFORMIO_UPLOAD_FLAGS="--auth=supersecret" platformio run --silent --target upload --upload-port ${IP}
