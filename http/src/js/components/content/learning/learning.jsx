import React from 'react';

import Room from './room.jsx';
import {learn, learnOnce} from "../../../api/learn";

export default class Learning extends React.Component {
    constructor(props) {
        super(props);
        this.state = {
            adding: false
        };
    }

    render () {
        const locationNames = Object.keys(this.context.store.getState().locations);
        const adding = this.state.adding;

        const addLocation = () => {
            const context = this;
            const roomName = context.addInput.value.toLowerCase();
            this.setState({ adding: true });
            learnOnce(roomName, () => {
                context.addInput.value = "";
                this.setState({ adding: false });
                learn(roomName);
            });
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
                                <th/>
                            </tr>
                            </thead>
                            <tbody>
                                {locationNames.map((location) => <Room key={location} location={location} />)}

                                <tr>
                                    <td>
                                        <p className="control has-addons">
                                            <input className="input" type="text" placeholder="SomeRoom" ref={(input) => { this.addInput = input; }} disabled={adding}/>
                                            <a className={adding ? "button is-loading" : "button"} onClick={addLocation} disabled={adding}>
                                                Add
                                            </a>
                                        </p>
                                    </td>
                                    <td>
                                    </td>
                                </tr>
                            </tbody>
                        </table>
                        {/*<div className="block control is-grouped">*/}
                            {/*<p className="control">*/}
                                {/*<input className="input" type="text" placeholder="SomeRoom" />*/}
                            {/*</p>*/}
                            {/*<p className="control">*/}
                                {/*<a className="button is-light" onClick={addLocation}>Add Location</a>*/}
                            {/*</p>*/}
                        {/*</div>*/}
                    </div>
                </div>
            </section>
        );
    }
}

Learning.contextTypes = {
    store: React.PropTypes.object
};