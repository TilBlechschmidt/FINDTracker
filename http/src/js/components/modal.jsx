import React from "react";
import {render} from "react-dom";

export function closeModal() {
    document.getElementById("modal-target").className = "modal";
}

export function showLoader(text) {
    showRawModal((
        <span>
            <div className="modal-background"></div>
            <div className="modal-content" style={{width: 'auto'}}>
                <div className="box has-text-centered" style={{lineHeight: '32px'}}>
                    <a className="button is-loading is-link" style={{marginRight: '0.75em'}}/>
                    {text}
                </div>
            </div>
        </span>
    ));
}

export function showModal(content, submitText, onSubmit, onCancel, submitClass, hideCancel) {
    showRawModal((
        <span>
            <div className="modal-background"></div>
            <Modal content={content} onCancel={onCancel} onSubmit={onSubmit} submitText={submitText}
                   submitClass={submitClass} hideCancel={hideCancel}/>
        </span>
    ));
}

export function showRawModal(content) {
    const target = document.getElementById("modal-target");
    render(content, target);
    target.className = "modal is-active";
}

class Modal extends React.Component {
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
        else closeModal();
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
                    <span className={this.props.hideCancel ? "column is-2 is-offset-11" : "column is-4 is-offset-9"}
                          style={{padding: 0}}>
                        {this.props.hideCancel ? null :
                            <a className={this.state.submitting ? "button is-disabled" : "button"}
                               onClick={this.onCancel}>Cancel</a>}
                        <a className={submitClassName} onClick={this.onSubmit}>{this.props.submitText}</a>
                    </span>
                </footer>
            </div>
        );
    }
}
