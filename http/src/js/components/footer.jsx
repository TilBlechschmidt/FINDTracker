import React from 'react';

export default class Footer extends React.Component {
    render () {
        return (
            <footer className="footer">
                <div className="container">
                    <div className="content has-text-centered">
                        <p>
                            <strong>FINDTracker</strong> by <a href="http://github.com/TheMegaTB">Til Blechschmidt</a>.
                        </p>
                        <hr/>
                        <p>
                            The source code is licensed <a href="http://opensource.org/licenses/mit-license.php">MIT</a>. The website content
                            is licensed <a href="http://creativecommons.org/licenses/by-nc-sa/4.0/">CC ANS 4.0</a>.
                        </p>
                    </div>
                </div>
            </footer>
        );
    }
}
