import React from 'react';

import {learn, stopLearning} from "../../../api/learn";

export default class Room extends React.Component {
    render () {
        const store = this.context.store;
        const state = store.getState();
        const locationName = this.props.location;
        const scanning = state.learning == locationName;
        const location = state.locations[locationName];

        const handleClick = () => {
            if (store.getState().learning == locationName)
                stopLearning();
            else
                learn(locationName);
        };

        return (
            <tr>
                <td style={{width: '25%'}}>{this.props.location.capitalizeFirstLetter()}</td>
                <td style={{width: '15%'}}>{location.count}</td>
                <td style={{width: '50%'}}>
                    <progress className="progress" value={location.accuracy} max="100">{location.accuracy}%</progress>
                </td>
                <td style={{width: '10%'}}>
                    <a className={scanning ? "button is-loading" : "button"} onClick={handleClick} style={{marginLeft: '10%', width: '80%', pointerEvents: 'auto'}}>
                        {scanning ? (<i className="fa fa-times-circle abort-learning"/>) : "Learn"}
                    </a>
                </td>
            </tr>
        );
    }
}

Room.contextTypes = {
    store: React.PropTypes.object
};