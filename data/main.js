function loadTemplate(name) {
    var renderTarget = document.querySelector(".render-target");
    var t = document.querySelector('template[name="' + name + '"]');
    var clone = document.importNode(t.content, true);

    while (renderTarget.hasChildNodes())
        renderTarget.removeChild(renderTarget.lastChild);

    renderTarget.appendChild(clone);
}

function reboot() {
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

function openModal(name) {
    var modal = document.querySelector(".modal." + name + "-modal");
    modal.className += " is-active";
}

function closeModal() {
    var modal = document.querySelector(".modal.is-active");
    modal.className = modal.className.replace("is-active", "");
}
