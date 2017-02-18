import React from 'react';

export default class Home extends React.Component {
    render () {
        return (
            <section className="hero is-fullheight">
                <div className="hero-body">
                    <div className="container has-text-centered">
                        <h3 className="title is-2">
                            <a href="http://github.com/TheMegaTB/FINDTracker/">
                                <span className="icon is-medium is-centered" style={{lineHeight: '43px', marginRight: '0.25em'}}>
                                    <i className="fa fa-compass" aria-hidden="true"/>
                                </span>
                                FINDTracker
                            </a>
                        </h3>
                        <h4 className="subtitle is-4">The easy way to track your position indoors</h4>
                    </div>
                </div>
            </section>
        );
    }
}
