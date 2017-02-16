const webpack = require('webpack'); //to access built-in plugins
const HtmlWebpackPlugin = require('html-webpack-plugin'); //installed via npm
const HtmlWebpackInlineSourcePlugin = require('html-webpack-inline-source-plugin');
const DashboardPlugin = require('webpack-dashboard/plugin');
const path = require('path');

let production = process.env.BUILD_PRODUCTION;

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

// const UglifyConfig = {
//     minimize: true,
//     sourceMap: !production
// };

const config = {
    entry: "./src/js/main.js",
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
    // config.plugins.push(new webpack.optimize.UglifyJsPlugin(UglifyConfig));
}

module.exports = config;
