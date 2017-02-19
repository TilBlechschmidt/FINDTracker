const webpack = require('webpack'); //to access built-in plugins
const HtmlWebpackPlugin = require('html-webpack-plugin'); //installed via npm
const HtmlWebpackInlineSourcePlugin = require('html-webpack-inline-source-plugin');
var CompressionPlugin = require("compression-webpack-plugin");
const DashboardPlugin = require('webpack-dashboard/plugin');
const path = require('path');

let production = process.env.NODE_ENV == 'production';

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

const config = {
    entry: "./src/js/main.jsx",
    devtool: 'source-map',
    output: {
        path: path.resolve(__dirname, 'dist'),
        publicPath: "/",
        filename: 'FINDTracker.bundle.js'
    },
    module: {
        rules: [
            { test: /\.css$/, loader: "style-loader!css-loader" },
            {
                test: /\.(js|jsx)$/,
                loader: 'babel-loader',
                query: {
                    presets: ['es2015', 'react']
                }
            }
        ]
    },
    plugins: [
        new HtmlWebpackPlugin(HTMLConfig),
        new webpack.DefinePlugin({
            PRODUCTION: production,
        }),
        new CompressionPlugin({
            asset: "[path].gz[query]",
            algorithm: "gzip",
            test: /\.js$|\.html$/,
            threshold: 10240,
            minRatio: 0.8
        })
    ],
    devServer: {
        stats: {
            chunks:false
        },
    }
};

if (production) {
    config.plugins.push(new HtmlWebpackInlineSourcePlugin());
} else {
    config.plugins.push(new DashboardPlugin());
}

module.exports = config;
