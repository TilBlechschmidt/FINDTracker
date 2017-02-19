import React from "react";
import {reboot} from "../api/networking";
import {showModal} from "./modal.jsx";

export default class Navigation extends React.Component {
    componentDidMount() {
        const store = this.context.store;
        this.checkbox.onchange = function (e) {
            store.dispatch({
                type: 'UPDATE_CFG',
                config: { active: e.target.checked }
            })
        };
    }

    reboot() {
        showModal((
            <div className="content">
                <h1>Reboot</h1>
                <p>Are you <strong>sure</strong> you want to reboot the FINDTracker? It may take some time for it to
                    reboot and reconnect to your configured WiFi network. Depending on your configuration it might not
                    be able to connect to your WiFi which would require a reset to factory defaults. For details please
                    consult the <a href="">manual</a>.</p>
            </div>
        ), "Reboot", () => {
            reboot();
        });
    }

    render() {
        const mobileHiddenClassName = "nav-item is-tab is-hidden-mobile";
        const tabletHiddenClassName = "nav-item is-tab is-hidden-tablet";
        const currentLocation = this.props.location;
        const store = this.context.store;
        const active = store.getState().config.active;

        function generateClassName(location, additional) {
            return additional + " " + (location == currentLocation ? "is-active" : undefined);
        }

        function navigate(location) {
            store.dispatch({
                type: 'NAVIGATE',
                location: location
            });
        }

        const checkbox = React.createElement('input', {
            type: 'checkbox',
            defaultChecked: active,
            id: "checkbox2",
            className: "ios-toggle",
            ref: (box) => this.checkbox = box
        });

        return (
            <nav className="nav has-shadow">
                <div className="container">
                    <div className="nav-left">
                        <a className="nav-item" id="compass-img">
                            <img src={require('url-loader!../../static/compass.png')} alt="FINDTracker"/>
                        </a>
                        <a className={generateClassName('home', mobileHiddenClassName)} onClick={navigate.bind(this, 'home')}>Home</a>
                        <a className={generateClassName('learning', mobileHiddenClassName)} onClick={navigate.bind(this, 'learning')}>Learning</a>
                        <a className={generateClassName('tracking', mobileHiddenClassName)} onClick={navigate.bind(this, 'tracking')}>Tracking</a>
                        <a className={generateClassName('wifi', mobileHiddenClassName)} onClick={navigate.bind(this, 'wifi')}>WiFi</a>
                    </div>
                    <span className="nav-toggle">
                    <span/>
                    <span/>
                    <span/>
                </span>
                    <div className="nav-right nav-menu">
                        <a className={generateClassName('home', tabletHiddenClassName)} onClick={navigate.bind(this, 'home')}>Home</a>
                        <a className={generateClassName('learning', tabletHiddenClassName)} onClick={navigate.bind(this, 'learning')}>Learning</a>
                        <a className={generateClassName('tracking', tabletHiddenClassName)} onClick={navigate.bind(this, 'tracking')}>Tracking</a>
                        <a className={generateClassName('wifi', tabletHiddenClassName)} onClick={navigate.bind(this, 'wifi')}>WiFi</a>
                        <a className="nav-item is-tab">
                            {checkbox}
                            <label htmlFor="checkbox2" className="checkbox-label" data-off="Not tracking" data-on=""/>
                        </a>
                        <a className="nav-item is-tab">Update</a>
                        {/* TODO Show a modal BEFORE rebooting (modal component maybe) */}
                        <a className="nav-item is-tab" onClick={this.reboot}>Reboot</a>
                    </div>
                </div>
            </nav>
        );
    }
}

Navigation.contextTypes = {
    store: React.PropTypes.object
};