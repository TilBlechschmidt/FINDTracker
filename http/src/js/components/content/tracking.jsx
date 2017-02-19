import React from "react";

const hostRegex = /^(([a-zA-Z0-9]|[a-zA-Z0-9][a-zA-Z0-9\-]*[a-zA-Z0-9])\.)*([A-Za-z0-9]|[A-Za-z0-9][A-Za-z0-9\-]*[A-Za-z0-9])$/g;
const portRegex = /^\d{2,}$/g;

const defaultHost = "ml.internalpositioning.com";
const defaultGroup = "FINDTracker";
const defaultUser = "Human";

export default class Tracking extends React.Component {
    constructor(props) {
        super(props);

        this.state = {
            hostValid: true,
            hostHint: "",
            hostValue: ""
        };

        this.onBlur = this.onBlur.bind(this);
        this.onChange = this.onChange.bind(this);
        this.hostValidityCheck = this.hostValidityCheck.bind(this);
    }

    hostValidityCheck() {
        const newValue = this.state.hostValue;

        const separatorIndex = newValue.indexOf(":");
        const hostname = separatorIndex > -1 ? newValue.substr(0, separatorIndex) : newValue;
        const port = newValue.substr(separatorIndex + 1);

        if (separatorIndex > -1 && !port.match(portRegex)) {
            this.setState({
                hostValid: false,
                hostHint: "The port number is not valid"
            });
            return false;
        }

        if (!hostname.match(hostRegex)) {
            this.setState({
                hostValid: false,
                hostHint: "The hostname or IP is not valid"
            });
            return false;
        }

        this.setState({
            hostValid: true,
            hostHint: ""
        });

        return true;
    }

    onChange(field, e) {
        if (field == "trackingHost") {
            let newValue = e.target.value ? e.target.value : defaultHost;

            this.setState({hostValue: newValue});

            if (this.validityCheck) clearTimeout(this.validityCheck);
            this.validityCheck = setTimeout(this.hostValidityCheck, 500);
        }
    }

    onBlur(field, e) {
        let newValue = e.target.value;

        clearTimeout(this.validityCheck);

        if (field == "trackingHost" && !this.hostValidityCheck()) return;

        if (newValue == "") {
            if (field == "trackingHost") newValue = defaultHost;
            if (field == "trackingGroup") newValue = defaultGroup;
            if (field == "trackingUser") newValue = defaultUser;
        }

        const cfg = {};
        cfg[field] = newValue;

        this.context.store.dispatch({
            type: 'UPDATE_CFG',
            config: cfg
        });
    }

    componentDidMount() {
        this.setState({
            hostValue: this.context.store.getState().config.trackingHost
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
                            <h3 className="title is-2">Tracking settings</h3>
                            <h4 className="subtitle is-4">Configuration properties regarding the tracking functionality</h4>
                        </div>
                    </div>
                </div>
                <div className="hero-body">
                    <div className="container">
                        <label className="label">
                            <h1 className="title is-4">Server</h1>
                            <h2 className="subtitle is-6">The hostname and port of the tracking server this device
                                should broadcast to.</h2>
                        </label>
                        <p className="control has-icon has-icon-right"
                           data-tooltip={this.state.hostHint ? this.state.hostHint : null}
                           data-tooltip-position="bottom">
                            <input className={this.state.hostValid ? "input" : "input is-danger"} type="text"
                                   placeholder={defaultHost} defaultValue={config.trackingHost}
                                   onChange={this.onChange.bind(this, "trackingHost")}
                                   onBlur={this.onBlur.bind(this, "trackingHost")}/>
                            {this.state.hostValid ? null :
                                <span className="icon is-small">
                                    <i className="fa fa-warning"/>
                                </span>
                            }
                        </p>
                        <br/>
                        <label className="label">
                            <h1 className="title is-4">Group</h1>
                            <h2 className="subtitle is-6">The group's name this device should be part of.</h2>
                        </label>
                        <p className="control">
                            <input className="input" type="text" placeholder={defaultGroup}
                                   defaultValue={config.trackingGroup}
                                   onChange={this.onChange.bind(this, "trackingGroup")}
                                   onBlur={this.onBlur.bind(this, "trackingGroup")}/>
                        </p>
                        <br/>
                        <label className="label">
                            <h1 className="title is-4">User</h1>
                            <h2 className="subtitle is-6">The person's name this tracker is carried by.</h2>
                        </label>
                        <p className="control">
                            <input className="input" type="text" placeholder={defaultUser}
                                   defaultValue={config.trackingUser}
                                   onChange={this.onChange.bind(this, "trackingUser")}
                                   onBlur={this.onBlur.bind(this, "trackingUser")}/>
                        </p>
                    </div>
                </div>
            </section>
        );
    }
}

Tracking.contextTypes = {
    store: React.PropTypes.object
};