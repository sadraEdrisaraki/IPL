// Getter, without setter, cannot be assigned : use strict
"use strict";

class Car {
  constructor(brand,model) {
    this.brand = brand;
    this.model = model;
    this._id = Math.random();
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
