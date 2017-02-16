import React from 'react';

export default class WiFi extends React.Component {
    render () {
        return (
            <section className="hero">
                <div className="hero-head">
                    <div className="container">
                        <div className="content has-text-centered" style={{paddingTop: '5em'}}>
                            <h3 className="title is-2">WiFi settings</h3>
                            <h4 className="subtitle is-4">Configuration properties regarding the network connectivity of the tracker</h4>
                        </div>
                    </div>
                </div>
                <div className="hero-body">
                    <div className="container">
                        <h1 className="title is-3">WLAN Client</h1>
                        <label className="label">
                            <h1 className="title is-4">SSID</h1>
                            <h2 className="subtitle is-6">The name of the network this device should connect to.</h2>
                        </label>
                        <p className="control has-icon has-icon-right">
                            <input className="input is-danger" type="text" placeholder="YourWiFiNetwork" />
                            <span className="icon is-small">
                                <i className="fa fa-warning"/>
                            </span>
                        </p>
                        <label className="label">
                            <h1 className="title is-4">Passphrase</h1>
                            <h2 className="subtitle is-6">The passphrase of your wireless network.</h2>
                        </label>
                        <p className="control">
                            <input className="input" type="password" placeholder="supersecret" />
                        </p>
                        <label className="label">
                            <h1 className="title is-4">Hostname</h1>
                            <h2 className="subtitle is-6">How this device should answer to name queries.</h2>
                        </label>
                        <p className="control">
                            <input className="input" type="text" placeholder="FINDTracker" />
                        </p>
                        <hr/>
                        <h1 className="title is-3">AccessPoint</h1>
                        <label className="label">
                            <h1 className="title is-4">Passphrase</h1>
                            <h2 className="subtitle is-6">The secret words the configuration network (AP) should be protected with.</h2>
                        </label>
                        <p className="control">
                            <input className="input" type="text" placeholder="supersecret" />
                        </p>
                    </div>
                </div>
            </section>
        );
    }
}