import React from 'react';

export default class Navigation extends React.Component {
    render () {
        return (
            <nav className="nav has-shadow">
                <div className="container">
                    <div className="nav-left">
                        <a className="nav-item" id="compass-img">
                            <img src={require('url-loader!../../static/compass.png')} alt="FINDTracker"/>
                        </a>
                        <a className="nav-item is-tab is-hidden-mobile" data-target="home">Home</a>
                        <a className="nav-item is-tab is-hidden-mobile" data-target="learning">Learning</a>
                        <a className="nav-item is-tab is-hidden-mobile" data-target="tracking">Tracking</a>
                        <a className="nav-item is-tab is-hidden-mobile" data-target="wifi">WiFi</a>
                    </div>
                    <span className="nav-toggle">
                    <span/>
                    <span/>
                    <span/>
                </span>
                    <div className="nav-right nav-menu">
                        <a className="nav-item is-tab is-hidden-tablet is-active">Home</a>
                        <a className="nav-item is-tab is-hidden-tablet">Learning</a>
                        <a className="nav-item is-tab is-hidden-tablet">Tracking</a>
                        <a className="nav-item is-tab is-hidden-tablet">WiFi</a>
                        <a className="nav-item is-tab">Update</a>
                        <a className="nav-item is-tab" data-modal="reboot">Reboot</a>
                    </div>
                </div>
            </nav>
        );
    }
}
