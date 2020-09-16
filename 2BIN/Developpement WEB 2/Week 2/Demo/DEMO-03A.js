"use strict";


function welcome() {
  // Maybe the dumbest function ever
  return "Welcome dear students ; )";
  
}

var btn = document.querySelector("button");
var msg = document.querySelector("div");
btn.onclick = function() {
  btn.innerText = "You clicked on me : )";
  msg.innerText = welcome();
  
};



