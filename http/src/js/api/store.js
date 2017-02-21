import {createStore} from "redux";
import {httpAsync} from "./networking";

const defaultState = {
    config: {},
    locations: {},
    learning: undefined,
    location: "home"
};

function updateConfig(obj) {
    if (PRODUCTION)
        httpAsync("/config", null, "POST", JSON.stringify(obj));
}

function appStore(state = defaultState, action) {
    switch (action.type) {
        case 'UPDATE_CFG':
            state.config = Object.assign(state.config, action.config);
            if (!action.noUpdate)
                updateConfig(action.config);
            break;
        case 'UPDATE_LOCATIONS':
            state.locations = action.locations;
            break;
        case 'LEARN':
            state.learning = action.room;
            break;
        case 'STOP_LEARNING':
            state.learning = undefined;
            break;
        case 'NAVIGATE':
            state.location = action.location;
            break;
        case 'TRACKED':
            state.trackedLocation = action.location;
    }

    console.log(action.type, state);

    return state;
}

export let store = createStore(appStore);
let locationSocket;
let trackedLocationReset;

export function reloadConfig(cb) {
    if (!PRODUCTION) {
        store.dispatch({
            type: 'UPDATE_CFG',
            config: {
                "auth": "supersecret2",
                "wifiReconnectionInterval": 60000,
                "SSID": "SomeSSID",
                "passphrase": "supersecret",
                "hostname": "FINDTracker",
                "active": false,
                "bufferSize": 10,
                "trackingHost": "10.0.0.38:18003",
                "trackingGroup": "Family",
                "trackingUser": "Til"
            },
            noUpdate: true
        });
        cb();
    }
    if (PRODUCTION) {
        httpAsync("/config", (cfg) => {
            cfg = JSON.parse(cfg);
            store.dispatch({
                type: 'UPDATE_CFG',
                config: cfg,
                noUpdate: true
            });
            if (typeof cb === 'function') cb();
        });
        if (locationSocket) locationSocket.close();
        locationSocket = new WebSocket("ws://" + location.hostname + ":81");
        locationSocket.onmessage = (msg) => {
            const newLocation = JSON.parse(msg.data).location;

            if (trackedLocationReset) clearTimeout(trackedLocationReset);
            trackedLocationReset = setTimeout(() => store.dispatch({ type: 'TRACKED', location: undefined }), 15000);

            if (newLocation != store.getState().trackedLocation)
                store.dispatch({
                    type: 'TRACKED',
                    location: newLocation.capitalizeFirstLetter()
                });
        }
    }
}