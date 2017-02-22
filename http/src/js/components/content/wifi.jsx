import React from 'react';

const defaultHostname = "FINDTracker";

export default class WiFi extends React.Component {
    constructor(props) {
        super(props);

        this.onBlur = this.onBlur.bind(this);
    }

    onBlur(field, e) {
        let newValue = e.target.value;

        if (newValue == "" && field == "hostname") newValue = defaultHostname;

        const cfg = {};
        cfg[field] = newValue;

        this.context.store.dispatch({
            type: 'UPDATE_CFG',
            config: cfg
        });
    }

    render () {
        const store = this.context.store;
        const config = store.getState().config;

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
                        <p className="control">
                            <input className="input" type="text" placeholder="YourWiFiNetwork" defaultValue={config.SSID} onBlur={this.onBlur.bind(this, "SSID")} />
                        </p>
                        <label className="label">
                            <h1 className="title is-4">Passphrase</h1>
                            <h2 className="subtitle is-6">The passphrase of your wireless network.</h2>
                        </label>
                        <p className="control">
                            <input className="input" type="password" placeholder="supersecret" defaultValue={config.passphrase} onBlur={this.onBlur.bind(this, "passphrase")} />
                        </p>
                        <label className="label">
                            <h1 className="title is-4">Hostname</h1>
                            <h2 className="subtitle is-6">How this device should answer to name queries.</h2>
                        </label>
                        <p className="control">
                            <input className="input" type="text" placeholder="FINDTracker" defaultValue={config.hostname} onBlur={this.onBlur.bind(this, "hostname")} />
                        </p>
                        {/*<hr/>*/}
                        {/*<h1 className="title is-3">AccessPoint</h1>*/}
                        {/*<label className="label">*/}
                            {/*<h1 className="title is-4">Passphrase</h1>*/}
                            {/*<h2 className="subtitle is-6">The secret words the configuration network (AP) should be protected with.</h2>*/}
                        {/*</label>*/}
                        {/*<p className="control">*/}
                            {/*<input className="input" type="text" placeholder="supersecret" />*/}
                        {/*</p>*/}
                    </div>
                </div>
            </section>
        );
    }
}

WiFi.contextTypes = {
    store: React.PropTypes.object
};