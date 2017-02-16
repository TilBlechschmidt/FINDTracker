import { createStore } from 'redux';
import { httpAsync } from './networking';

const defaultState = {
    config: {},
    learning: undefined
};

function updateConfig(obj) {
    httpAsync("/config", null, "POST", JSON.stringify(obj));
}

function appStore(state = defaultState, action) {
    switch (action.type) {
        case 'UPDATE_CFG':
            state.config = Object.assign(state.config, action.config);
            if (!action.noUpdate)
                updateConfig(action.config);
            break;
        case 'LEARN':
            state.learning = action.room;
            break;
        case 'STOP_LEARNING':
            state.learning = undefined;
            break;
    }

    return state;
}

export let store = createStore(appStore);

export function reloadConfig(cb) {
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

store.subscribe(() =>
  console.log(store.getState())
);
