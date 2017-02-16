import React from 'react';
import {Provider} from "react-redux";
import {render} from 'react-dom';

import {store} from "./api/store";

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

const renderApp = _ => {
    render(
        <Provider store={store}>
            <App/>
        </Provider>,
        document.getElementById('render-target')
    )
};

store.subscribe(renderApp);
renderApp();
