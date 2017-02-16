import { createStore } from 'redux';
import { httpAsync } from './networking';

const defaultState = {
    config: {},
    locations: {},
    learning: undefined
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
    }

    console.log(action.type, state);

    return state;
}

export let store = createStore(appStore);

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
                "trackingURL": "http://10.0.0.38:18003/track",
                "trackingGroup": "Family",
                "trackingUser": "Til"
            },
            noUpdate: true
        });
        cb();
    }
    if (PRODUCTION)
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