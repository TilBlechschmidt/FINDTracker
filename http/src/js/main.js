import {updateLocations} from "./api/learn";
import {reloadConfig} from "./api/store";

import "./helpers";
import "./app.jsx";
import "../css/styles";

reloadConfig(() => {
        updateLocations();
});

document.body.className += " loaded";
