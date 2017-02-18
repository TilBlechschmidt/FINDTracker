import React from 'react';
import {reboot} from "../api/networking";

export default class Navigation extends React.Component {
    render () {
        const mobileHiddenClassName = "nav-item is-tab is-hidden-mobile";
        const tabletHiddenClassName = "nav-item is-tab is-hidden-tablet";
        const currentLocation = this.props.location;
        const store = this.context.store;

        function generateClassName(location, additional) {
            return additional + " " + (location == currentLocation ? "is-active" : undefined);
        }

        function navigate(location) {
            store.dispatch({
                type: 'NAVIGATE',
                location: location
            });
        }

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
                        <a className="nav-item is-tab">Update</a>
                        {/* TODO Show a modal BEFORE rebooting (modal component maybe) */}
                        <a className="nav-item is-tab" onClick={reboot}>Reboot</a>
                    </div>
                </div>
            </nav>
        );
    }
}

Navigation.contextTypes = {
    store: React.PropTypes.object
};