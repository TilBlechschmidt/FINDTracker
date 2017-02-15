const webpack = require('webpack'); //to access built-in plugins
const HtmlWebpackPlugin = require('html-webpack-plugin'); //installed via npm
const HtmlWebpackInlineSourcePlugin = require('html-webpack-inline-source-plugin');
const path = require('path');

let production = process.env.BUILD_PRODUCTION ? true : false;

const HTMLConfig = {
    template: './src/index.html',
    minify: {
        minifyCSS: true,
        minifyJS: true,
        removeComments: production,
        collapseWhitespace: true,
        conservativeCollapse: true,
    },
    inlineSource: production ? '.(js|css)$' : undefined
};

const UglifyConfig = {
    minimize: true,
    sourceMap: !production
};

const config = {
    entry: "./src/entry.js",
    devtool: 'source-map',
    output: {
        path: path.resolve(__dirname, 'dist'),
        publicPath: "/",
        filename: 'FINDTracker.bundle.js'
    },
    module: {
        rules: [
            { test: /\.css$/, loader: "style-loader!css-loader" },
            { test: /\.(js|jsx)$/, use: 'babel-loader' }
        ]
    },
    plugins: [
        new webpack.optimize.UglifyJsPlugin(UglifyConfig),
        new HtmlWebpackPlugin(HTMLConfig)
    ],
    devServer: {
        stats: {
            chunks:false
        },
    }
};

if (production) {
    config.plugins.push(new HtmlWebpackInlineSourcePlugin());
}

module.exports = config;
