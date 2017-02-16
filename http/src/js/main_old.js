// import * as Mustache from "mustache";

// var img = document.createElement('img');
// img.src = require('url-loader!../static/compass.png');
// document.getElementById("compass-img").appendChild(img);

export function navigate(name) {
    var navElements = document.querySelectorAll(".nav-item");
    navElements.forEach(function (el) {
        el.className = el.className.replace("is-active", "");
        if (el.dataset && el.dataset.target && el.dataset.target == name)
            el.className += " is-active";
    });
    // loadTemplate(name);
}

// function loadTemplate(name) {
//     var template = document.querySelector("#template-" + name).innerHTML;
//     Mustache.parse(template);
//     document.querySelector(".render-target").innerHTML =
//                             Mustache.render(template, { something: "test"});
// }

function makeLoading(e) {
    e.className = e.className + " is-loading";
}

export function openModal(name) {
    var modal = document.querySelector(".modal." + name + "-modal");
    modal.className += " is-active";
}

export function closeModal() {
    var modal = document.querySelector(".modal.is-active");
    modal.className = modal.className.replace("is-active", "");
}
