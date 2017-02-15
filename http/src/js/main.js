import * as Mustache from "mustache";

var img = document.createElement('img');
img.src = require('url-loader!../static/compass.png');
document.getElementById("compass-img").appendChild(img);

export function navigate(name) {
    var navElements = document.querySelectorAll(".nav-item");
    navElements.forEach(function (el) {
        el.className = el.className.replace("is-active", "");
        if (el.dataset && el.dataset.target && el.dataset.target == name)
            el.className += " is-active";
    });
    loadTemplate(name);
}

function loadTemplate(name) {
    var template = document.querySelector("#template-" + name).innerHTML;
    Mustache.parse(template);
    document.querySelector(".render-target").innerHTML =
                            Mustache.render(template, { something: "test"});
}

export function reboot() {
    var modal = document.querySelector(".modal.reboot-modal");
    var rebootButton = modal.querySelector(".button.is-success");
    var cancelButton = modal.querySelector(".button:not(.is-success)");

    rebootButton.className += " is-loading";
    cancelButton.className += " is-disabled";

    httpGetAsync('/reboot', function (res) {
        window.location.href = window.location.href;
    });
}

function makeLoading(e) {
    e.className = e.className + " is-loading";
}

function httpGetAsync(theUrl, callback) {
    var xmlHttp = new XMLHttpRequest();
    xmlHttp.onreadystatechange = function() {
        if (xmlHttp.readyState == 4 && xmlHttp.status == 200)
            callback(xmlHttp.responseText);
    }
    xmlHttp.open("GET", theUrl, true); // true for asynchronous
    xmlHttp.send(null);
}

export function openModal(name) {
    var modal = document.querySelector(".modal." + name + "-modal");
    modal.className += " is-active";
}

export function closeModal() {
    var modal = document.querySelector(".modal.is-active");
    modal.className = modal.className.replace("is-active", "");
}
