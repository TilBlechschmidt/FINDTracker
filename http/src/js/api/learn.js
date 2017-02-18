import {httpAsync} from "./networking";
import {store} from "./store";

function getTrackingServer() {
    return "http://" + store.getState().config.trackingHost;
}

function recalculate(cb) {
    const callback = () => {
        updateLocations();
        if (typeof cb === 'function') cb();
    };

    if (!PRODUCTION) callback();
    if (PRODUCTION) {
        const group = store.getState().config.trackingGroup;
        httpAsync(getTrackingServer() + "/calculate?group=" + group, callback);
    }
}

function sendFingerprints(fingerprints, cb) {
    if (!PRODUCTION) recalculate(cb);
    if (PRODUCTION)
        httpAsync(getTrackingServer() + "/learn", (res) => {
            res = JSON.parse(res);
            if (!res.success) throw "Error whilst sending fingerprints (" + res.message + ")!";
            recalculate(cb); // TODO: Run recalculate only when inserting new locations
        }, "POST", JSON.stringify(fingerprints));
}

function getFingerprints(cb) {
    if (!PRODUCTION) {
        const cfg = store.getState().config;
        setTimeout(() => {
            cb({
                group: cfg.trackingGroup,
                username: cfg.trackingUser,
                "wifi-fingerprint": []
            });
        }, 7000);
    }
    if (PRODUCTION)
        httpAsync("/scan", (env) => {
            env = JSON.parse(env);
            if (typeof cb === 'function') cb(env);
        });
}

export function updateLocations() {
    if (!PRODUCTION) {
        store.dispatch({
            type: 'UPDATE_LOCATIONS',
            locations: {
                "bedroom": { accuracy: 90, count: 14 },
                "livingroom": { accuracy: 15, count: 2 },
            }
        });
    }
    if (PRODUCTION) {
        const group = store.getState().config.trackingGroup;
        httpAsync(getTrackingServer() + "/locations?group=" + group, (locations) => {
            locations = JSON.parse(locations);
            store.dispatch({
                type: 'UPDATE_LOCATIONS',
                locations: locations.locations
            });
        });
    }
}

export function learnOnce(roomName, cb) {
    getFingerprints((fingerprints) => {
        console.log("Found " + fingerprints['wifi-fingerprint'].length + " networks.");
        fingerprints.location = roomName;
        sendFingerprints(fingerprints, cb);
    });
}

export function learn(roomName, noInit) {
    if (typeof roomName === 'string') roomName = roomName.toLowerCase();
    if (!noInit)
        store.dispatch({
            type: 'LEARN',
            room: roomName
        });
    else
        roomName = store.getState().learning;

    if (roomName)
        learnOnce(roomName, learn.bind(this, null, true));
}

export function stopLearning() {
    store.dispatch({ type: 'STOP_LEARNING' });
}
