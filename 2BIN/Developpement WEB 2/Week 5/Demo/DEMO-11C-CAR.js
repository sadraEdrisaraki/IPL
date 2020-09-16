"use strict";

// Import of a node.js package ! This method is not valid for client side script !!!
const shortid = require("shortid");

class Car {
  constructor(brand,model) {
    this.brand = brand;
    this.model = model;
    this._id = shortid.generate();
  }
  get id() {
    return this._id;
  }
  getDescription() {
    return "Car's description : " + this.brand + ", " + this.model + " , ID:" + this.id;
  }
}

// Named export of 
export {Car};