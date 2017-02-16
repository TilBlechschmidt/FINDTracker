import React from 'react';

export default class Room extends React.Component {
    render () {
        return (
            <tr>
                <td style={{width: '25%'}}>Bedroom</td>
                <td style={{width: '15%'}}>20</td>
                <td style={{width: '50%'}}>
                    <progress className="progress" value="15" max="100">15%</progress>
                </td>
                <td style={{width: '10%'}}>
                    <a className="button">Learn</a>
                </td>
            </tr>
        );
    }
}