import React from 'react';

export default class Tracking extends React.Component {
    render () {
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
                            <h2 className="subtitle is-6">The URL of the tracking server this device should broadcast to.</h2>
                        </label>
                        <p className="control has-icon has-icon-right">
                            <input className="input is-danger" type="text" placeholder="http://ml.internalpositioning.com/track" />
                            <span className="icon is-small">
                                <i className="fa fa-warning"/>
                            </span>
                        </p>
                        <br/>
                        <label className="label">
                            <h1 className="title is-4">Group</h1>
                            <h2 className="subtitle is-6">The group's name this device should be part of.</h2>
                        </label>
                        <p className="control">
                            <input className="input" type="text" placeholder="Family" value="bulma" />
                        </p>
                        <br/>
                        <label className="label">
                            <h1 className="title is-4">User</h1>
                            <h2 className="subtitle is-6">The user's name this device is carried by.</h2>
                        </label>
                        <p className="control">
                            <input className="input" type="text" placeholder="Bob" />
                        </p>
                    </div>
                </div>
            </section>
        );
    }
}