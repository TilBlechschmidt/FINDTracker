npm i
NODE_ENV="production" ./node_modules/webpack/bin/webpack.js --hide-modules -p
mkdir -p dist/SPIFFS
gzip -9 < dist/index.html > dist/SPIFFS/index.html.gz
#cp dist/index.html dist/SPIFFS/
