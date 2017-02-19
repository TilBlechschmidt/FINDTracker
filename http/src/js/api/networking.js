export function httpAsync(theUrl, callback, type, payload, errorCB) {
    const xmlHttp = new XMLHttpRequest();
    xmlHttp.timeout = 30000; // Set timeout to 30s 'cause ESPs are slow
    xmlHttp.onreadystatechange = function() {
        if (xmlHttp.readyState == 4 && xmlHttp.status == 200)
            if (typeof callback === 'function') callback(xmlHttp.responseText);
            else if (typeof errorCB === 'function')
                errorCB();
    };
    xmlHttp.onerror = errorCB;
    xmlHttp.open(type ? type : "GET", theUrl, true); // true for asynchronous
    xmlHttp.send(payload);
}

export function reboot() {
    if (!PRODUCTION)
        setTimeout(() => {
            window.location.href = window.location.href;
        }, 3000);
    if (PRODUCTION)
        httpAsync('/reboot', function (res) {
            window.location.href = window.location.href;
        });
}
