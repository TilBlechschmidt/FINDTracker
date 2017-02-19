import React from "react";
import {render} from "react-dom";

export function closeModal() {
    document.getElementById("modal-target").className = "modal";
}

export function showModal(content, submitText, onSubmit, onCancel, submitClass) {
    const target = document.getElementById("modal-target");
    render((
        <span>
            <div className="modal-background"></div>
            <Modal content={content} onCancel={onCancel} onSubmit={onSubmit} submitText={submitText}
                   submitClass={submitClass}/>
        </span>
    ), target);
    target.className = "modal is-active";
}

export default class Modal extends React.Component {
    constructor(props) {
        super(props);

        this.state = {
            submitting: false
        };

        this.onSubmit = this.onSubmit.bind(this);
        this.onCancel = this.onCancel.bind(this);
    }

    onSubmit() {
        this.setState({submitting: true});
        if (typeof this.props.onSubmit === 'function') this.props.onSubmit();
    }

    onCancel() {
        if (typeof this.props.onCancel === 'function') this.props.onCancel();
        else closeModal();
    }

    render() {

        let submitClassName = "button";

        if (typeof this.props.submitClass === 'string') submitClassName += " " + this.props.submitClass;
        else submitClassName += " is-success";

        if (this.state.submitting) submitClassName += " is-loading";

        return (
            <div className="modal-card">
                <section className="modal-card-body">
                    {this.props.content}
                </section>
                <footer className="modal-card-foot">
                    <span className="column is-4 is-offset-9" style={{padding: 0}}>
                        <a className={this.state.submitting ? "button is-disabled" : "button"} onClick={this.onCancel}>Cancel</a>
                        <a className={submitClassName} onClick={this.onSubmit}>{this.props.submitText}</a>
                    </span>
                </footer>
            </div>
        );
    }
}
