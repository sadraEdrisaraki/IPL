// Getter, without setter, cannot be assigned : use strict
"use strict";
// Import of a node.js package ! This method is not valid for client side script !!!
const shortid = require("shortid");

class Car {
  constructor(brand,model) {
    this.brand = brand;
    this.model = model;
    this._id = shortid.generate();
    //this._id = Math.random();
  }
  get id() {
    return this._id;
  }
  getDescription() {
    console.log("Car's description : " + this.brand + ", " + this.model + " , ID:" + this.id);
  }
}

var dacia = new Car("Dacia", "Sandero");
dacia.getDescription();
