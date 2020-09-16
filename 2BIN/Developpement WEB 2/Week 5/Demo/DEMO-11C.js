"use strict";
// Import of a node.js package ! This method is not valid for client side script !!!
//const shortid = require('shortid');

import {Car} from "./DEMO-11C-CAR.js";

var btn = document.querySelector("button");
var msg = document.querySelector("div");

btn.onclick = function() {
  btn.innerText = "You clicked on me : )";
  var dacia = new Car("Dacia", "Sandero");
  msg.innerText = dacia.getDescription();
  
};



