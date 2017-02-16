import React from 'react';
import {render} from 'react-dom';

// Page structure
import Navigation from './components/navigation.jsx';
import Footer from './components/footer.jsx';

// Page content
import Home from './components/content/home.jsx';
import Learning from './components/content/learning/learning.jsx';

// Miscellaneous
import RebootModal from './components/modals/reboot.jsx';


class App extends React.Component {
    render () {
        return (
            <div>
                <Navigation/>
                {/*<Home/>*/}
                <Learning/>
                <Footer/>

                {/*<RebootModal/>*/}
            </div>
        );
    }
}

render(<App/>, document.getElementById('render-target'));
