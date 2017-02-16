export function httpAsync(theUrl, callback, type, payload) {
    var xmlHttp = new XMLHttpRequest();
    xmlHttp.timeout = 30000; // Set timeout to 30s 'cause ESPs are slow
    xmlHttp.onreadystatechange = function() {
        if (xmlHttp.readyState == 4 && xmlHttp.status == 200 && typeof callback === 'function')
            callback(xmlHttp.responseText);
    }
    xmlHttp.open(type ? type : "GET", theUrl, true); // true for asynchronous
    xmlHttp.send(payload);
}

function getConfig() {
    httpAsync("/config", function (conf) {
        console.log(conf);
    });
}

function updateConfig(key, value) {
    const delta = {};
    delta[key] = value;
    httpAsync("/config", function () {}, "POST", JSON.stringify(delta));
}

export function reboot() {
    var modal = document.querySelector(".modal.reboot-modal");
    var rebootButton = modal.querySelector(".button.is-success");
    var cancelButton = modal.querySelector(".button:not(.is-success)");

    rebootButton.className += " is-loading";
    cancelButton.className += " is-disabled";

    httpAsync('/reboot', function (res) {
        window.location.href = window.location.href;
    });
}
