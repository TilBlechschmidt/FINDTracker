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
                            The source code is licensed <a href="https://github.com/TheMegaTB/FINDTracker/blob/master/License.txt">AGPL-3.0</a>. The website content
                            is licensed <a href="http://opensource.org/licenses/mit-license.php">MIT</a>.
                        </p>
                    </div>
                </div>
            </footer>
        );
    }
}
