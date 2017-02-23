DEST="../data/"

npm i
NODE_ENV="production" ./node_modules/webpack/bin/webpack.js --hide-modules -p
mkdir -p ${DEST}
gzip -9 < dist/index.html > "${DEST}index.html.gz"
