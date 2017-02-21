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

    return state;
}

export let store = createStore(appStore);
let locationSocket;
let trackedLocationReset;
let wsWatchdog;

function connectTrackingSocket() {
    if (locationSocket) locationSocket.close();
    locationSocket = new WebSocket("ws://" + location.hostname + ":81");

    locationSocket.onmessage = (msg) => {
        if (msg.data == "watchdog") {
            if (wsWatchdog) clearTimeout(wsWatchdog);
            wsWatchdog = setTimeout(() => {
                console.warn("Lost tracking connection!");
                connectTrackingSocket();
            }, 15000);
        } else {
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
        connectTrackingSocket();
        httpAsync("/config", (cfg) => {
            cfg = JSON.parse(cfg);
            store.dispatch({
                type: 'UPDATE_CFG',
                config: cfg,
                noUpdate: true
            });
            if (typeof cb === 'function') cb();
        });
    }
}