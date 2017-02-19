const HTTP_TIMEOUT = 30000;

export function httpAsync(theUrl, callback, type, payload, errorCB) {
    const xmlHttp = new XMLHttpRequest();
    const timeout = setTimeout(() => {
        xmlHttp.abort();
        if (typeof errorCB === 'function') errorCB();
    }, HTTP_TIMEOUT);

    xmlHttp.timeout = HTTP_TIMEOUT; // Set timeout to 30s 'cause ESPs are slow
    xmlHttp.onreadystatechange = function() {
        if (xmlHttp.readyState == 4 && xmlHttp.status == 200) {
            clearTimeout(timeout);
            if (typeof callback === 'function') callback(xmlHttp.responseText);
            else if (typeof errorCB === 'function') errorCB();
        }
    };
    xmlHttp.onerror = () => {
        clearTimeout(timeout);
        if (typeof errorCB === 'function') errorCB();
    };

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
