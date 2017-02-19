import {showLoader, closeModal} from "./components/modal.jsx";
import {updateLocations} from "./api/learn";
import {reloadConfig} from "./api/store";
import "./helpers";
import "./app.jsx";
import "../css/styles";

document.body.className += " loaded";
showLoader("Please wait while loading the configuration ...");

reloadConfig(() => {
    // TODO Show error when authentication failed
    closeModal();
    updateLocations();
});
