"use strict";

let libraries = ["Anime.js", "Three.js", "Phaser.io", "GSAP", "Mo.js", "Velocity", "..."];
//let html_text = "<ul>";
// to demonstrate the use of bootstrap, the List group and a breakpoint : https://getbootstrap.com/docs/4.3/components/list-group/
let html_text ="<ul class='list-group list-group-horizontal-lg'>";

// dynamically writing HTML code through a classical loop
for (let i = 0; i < libraries.length; i++) {
    //html_text += "<li>" + libraries[i] + "</li>";
    // to demonstrate the use of bootstrap and the List group
    html_text += "<li class='list-group-item'>" + libraries[i] + "</li>";
}

html_text += "</ul>";

// dynamically writing HTML code through forEach method
 html_text+="<ul class='list-group list-group-horizontal-lg'>";
libraries.forEach(function(value,index,array){
    html_text += "<li class='list-group-item'>" + value + "</li>";
})
html_text += "</ul>"; 

// setting the html content of the p#msg element through JQuery
$("#msg").html(html_text);
// or with the DOM Api
//document.getElementById("msg").innerHTML = text;

// Same thing by working directly with DOM elements
var list = document.createElement("ul");
list.className="list-group list-group-horizontal-lg";
for (let i = 0; i < libraries.length; i++) {
    //html_text += "<li>" + libraries[i] + "</li>";
    // to demonstrate the use of bootstrap and the List group
    var item = document.createElement("li");
    item.className = "list-group-item";
    item.innerText = libraries[i] ;
    list.appendChild(item);
}
$("#msg").append(list);

