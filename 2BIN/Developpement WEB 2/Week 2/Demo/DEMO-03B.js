"use strict";


function welcome() {
  // Maybe the dumbest function ever
  return "Welcome dear students ; )";
  
}


$(document).ready(function () {

  $("button").click(function (e) {
      $("div").text("You clicked on me : )"); 
      $("div").text(welcome());
  });

});

/* OLD CODE WITHOUT JQuery
var btn = document.querySelector("button");
var msg = document.querySelector("div");

btn.onclick = function() {
  btn.innerText = "You clicked on me : )";
  msg.innerText = welcome();
  
}; */


