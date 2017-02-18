import React from 'react';

export default class Modal extends React.Component {
    render () {
        return (
            <div className="modal-card">
                <section className="modal-card-body">
                <div className="content">
                <h1>Reboot</h1>
                <p>Are you <strong>sure</strong> you want to reboot the FINDTracker? It may take some time for it to reboot and reconnect to your configured WiFi network. Depending on your configuration it might not be able to connect to your WiFi which would require a reset to factory defaults. For details please consult the <a href="">manual</a>.</p>
            </div>
            </section>
            <footer className="modal-card-foot">
                <span className="column is-4 is-offset-9" style={{padding:0}}>
                <a className="button close-modal">Cancel</a>
                <a className="button is-success" id="reboot">Reboot</a>
                </span>
                </footer>
            </div>
        );
    }
}
