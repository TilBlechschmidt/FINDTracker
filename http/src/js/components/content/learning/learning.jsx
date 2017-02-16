import React from 'react';

import Room from './room.jsx';
import {learn} from "../../../api/learn";

export default class Learning extends React.Component {
    render () {
        const locationNames = Object.keys(this.context.store.getState().locations);

        const test = () => {
            console.log('hi');
            learn("Testroom");
        };

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
                                {locationNames.map((location) => <Room key={location} location={location} />)}
                            </tbody>
                        </table>
                        <div className="block">
                            <a className="button is-light" onClick={test}>Add Location</a>
                        </div>
                    </div>
                </div>
            </section>
        );
    }
}

Learning.contextTypes = {
    store: React.PropTypes.object
};