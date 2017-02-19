import React from "react";
import Room from "./room.jsx";
import {learn, learnOnce} from "../../../api/learn";
import {showModal, showLoader, closeModal} from "../../modal.jsx";
import {httpAsync} from "../../../api/networking";

export default class Learning extends React.Component {
    constructor(props) {
        super(props);
        this.state = {
            adding: false
        };
    }

    componentDidMount() {
        if (PRODUCTION || !PRODUCTION) {
            const store = this.context.store;
            const config = store.getState().config;
            showLoader("Please wait while connecting to the tracking server ...");
            httpAsync("http://" + config.trackingHost + "/locations?group=" + config.trackingGroup, closeModal, "GET", null, (a) => {
                console.log("CANCEL CALLBACK", a);
                store.dispatch({
                    type: 'NAVIGATE',
                    location: 'home'
                });
                closeModal();
                showModal((
                    <div className="content">
                        <h1>Houston, we've got a problem!</h1>
                        <p>I'm terribly sorry but we weren't able to connect to the tracking server hence you cannot run
                            the
                            learning process. Please make sure that <strong>your</strong> computer can reach the
                            tracking server. This is necessary since your browser takes care of the learning process
                            utilizing
                            the data received from your tracker.</p>
                    </div>
                ), "Ok", null, null, null, true);
            });
        }
    }

    render () {
        const locationNames = Object.keys(this.context.store.getState().locations);
        const adding = this.state.adding;

        const addLocation = () => {
            const context = this;
            const roomName = context.addInput.value.toLowerCase().replace(/\s/g,'');
            if (roomName == "") return;
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
                                            <input className="input" type="text" placeholder="New room" ref={(input) => { this.addInput = input; }} disabled={adding}/>
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
                    </div>
                </div>
            </section>
        );
    }
}

Learning.contextTypes = {
    store: React.PropTypes.object
};