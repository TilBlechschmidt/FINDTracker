import React from 'react';

import Room from './room.jsx';

export default class Learning extends React.Component {
    render () {
        return (
            <section className="hero">
                <div className="hero-head">
                    <div className="container">
                        <div className="content has-text-centered" style={{paddingTop: '5em'}}>
                            <h3 className="title is-2">Location learning</h3>
                            <h4 className="subtitle is-4">Learn the fingerprints for locations you want to track in</h4>
                        </div>
                    </div>
                </div>
                <div className="hero-body">
                    <div className="container">
                        <table className="table">
                            <thead>
                            <tr>
                                <th>Room name</th>
                                <th>Fingerprints</th>
                                <th>Accuracy</th>
                                <th/>
                            </tr>
                            </thead>
                            <tbody>
                                <Room/>
                            </tbody>
                        </table>
                        <div className="block">
                            <a className="button is-light">Add Location</a>
                        </div>
                    </div>
                </div>
            </section>
        );
    }
}