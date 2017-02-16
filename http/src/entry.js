import {navigate, closeModal, openModal} from "./js/main";
import {reboot} from "./js/networking";
import {learnOnce, updateLocations} from "./js/learn";
import {reloadConfig} from "./js/store";
import "../node_modules/bulma/css/bulma.css";

function learn(i) {
    if (i > 0) {
        learnOnce("bedroom", learn.bind(this, i-1));
    }
}

reloadConfig(() => {
    learn(100);
    updateLocations();
});

const navLinks = document.querySelectorAll(".nav-item[data-target]");
for (var navLink in navLinks) {
    if (!navLinks.hasOwnProperty(navLink)) continue;
    navLinks[navLink].onclick = function (e) {
        navigate(e.target.dataset.target);
    }
}

const closeModals = document.querySelectorAll(".close-modal");
for (var el in closeModals) {
    if (!closeModals.hasOwnProperty(el)) continue;
    closeModals[el].onclick = closeModal;
}

const openModals = document.querySelectorAll("[data-modal]");
for (var el in openModals) {
    if (!openModals.hasOwnProperty(el)) continue;
    el = openModals[el];
    el.onclick = openModal.bind(this, el.dataset.modal);
}

document.getElementById("reboot").onclick = reboot;

navigate("home");

document.body.className += " loaded";
