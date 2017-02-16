// import {navigate, closeModal, openModal} from "./js/main";
// import {reboot} from "./js/api/networking";
import {learn, stopLearning, updateLocations} from "./api/learn";
import {reloadConfig} from "./api/store";

import "./app.jsx";
import "../css/styles";

reloadConfig(() => {
    learn("bedroom");
    setTimeout(() => {
        stopLearning();
        updateLocations();
    }, 60000);
});

// const navLinks = document.querySelectorAll(".nav-item[data-target]");
// for (var navLink in navLinks) {
//     if (!navLinks.hasOwnProperty(navLink)) continue;
//     navLinks[navLink].onclick = function (e) {
//         navigate(e.target.dataset.target);
//     }
// }
//
// const closeModals = document.querySelectorAll(".close-modal");
// for (var el in closeModals) {
//     if (!closeModals.hasOwnProperty(el)) continue;
//     closeModals[el].onclick = closeModal;
// }
//
// const openModals = document.querySelectorAll("[data-modal]");
// for (var el in openModals) {
//     if (!openModals.hasOwnProperty(el)) continue;
//     el = openModals[el];
//     el.onclick = openModal.bind(this, el.dataset.modal);
// }
//
// document.getElementById("reboot").onclick = reboot;
//
// navigate("home");

document.body.className += " loaded";
