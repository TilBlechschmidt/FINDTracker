npm i
NODE_ENV="production" ./node_modules/webpack/bin/webpack.js --hide-modules -p
mkdir -p dist/SPIFFS
cp dist/index.html dist/SPIFFS/
