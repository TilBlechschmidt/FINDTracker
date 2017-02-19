import React from "react";
import {Provider} from "react-redux";
import {render} from "react-dom";
import {store} from "./api/store";
// Page structure
import Navigation from "./components/navigation.jsx";
import Footer from "./components/footer.jsx";
// Page content
import Home from "./components/content/home.jsx";
import WiFi from "./components/content/wifi.jsx";
import Tracking from "./components/content/tracking.jsx";
import Learning from "./components/content/learning/learning.jsx";

class App extends React.Component {
    render () {
        const location = this.context.store.getState().location;

        let content;
        switch (location) {
            case "home":
                content = <Home/>;
                break;
            case "learning":
                content = <Learning/>;
                break;
            case "tracking":
                content = <Tracking/>;
                break;
            case "wifi":
                content = <WiFi/>;
        }
        return (
            <div>
                <Navigation location={location} />
                {content}
                <Footer/>
            </div>
        );
    }
}

App.contextTypes = {
    store: React.PropTypes.object
};

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
