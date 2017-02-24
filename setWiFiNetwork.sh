SSID=$1
PWD=$2

IP="10.10.10.1"

curl --data "{ 'SSID': '${SSID}', 'passphrase': '${PWD}' }" ${IP}/config
curl ${IP}/reboot
