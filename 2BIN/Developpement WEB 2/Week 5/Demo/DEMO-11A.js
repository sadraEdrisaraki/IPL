"use strict";
// Import of a node.js package ! This method is not valid for client side script !!!
//const shortid = require('shortid');

import {Car} from "./DEMO-11A-CAR.js";
// import default export
//import auto from "./DEMO-11A-CAR.js";

var btn = document.querySelector("button");
var msg = document.querySelector("div");

btn.onclick = function() {
  btn.innerText = "You clicked on me : )";
  var dacia = new Car("Dacia", "Sandero");
  //var dacia = new auto("Dacia", "Sandero");
  msg.innerText = dacia.getDescription();
  
};



