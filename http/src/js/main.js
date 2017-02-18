import {updateLocations} from "./api/learn";
import {reloadConfig} from "./api/store";

import "./helpers";
import "./app.jsx";
import "../css/styles";

reloadConfig(() => {
    // TODO Show error when authentication failed
    updateLocations();
});

document.body.className += " loaded";
