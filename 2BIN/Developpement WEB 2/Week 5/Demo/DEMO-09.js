"use strict";
let raphael = {
    firstname: "Raphael",
    lastname: "Baroni",
    sayHello: () => "Hello à tous"
};

console.log(
    "Message de " +
    raphael.firstname +
    " " +
    raphael.lastname +
    " : " +
    raphael.sayHello()
);

let sandra = {};
sandra.firstname = "Sandra";
sandra.lastname = "Parisi";
console.log(
    sandra.firstname,
    sandra.lastname,
    sandra["firstname"],
    sandra["lastname"]
);
