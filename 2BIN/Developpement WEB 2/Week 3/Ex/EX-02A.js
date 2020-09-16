"use strict";

var nbr_rect = 101;

var fps = 5; // frame per second
var reqanimationreference; // référence vers l'animation
var animate = true;
var size = 5;
var timer;
var color;

let myCanvas = document.querySelector("canvas");
myCanvas.width = document.documentElement.clientWidth / 2;
myCanvas.height = document.documentElement.clientHeight / 2;
let myContext = myCanvas.getContext("2d");
myContext.fillStyle = "blue";

function draw_2D() {
  timer = setTimeout(function() {
    //on efface tout ce qui a été fait lors de la frame précédente
    //une autre façon de faire et de redéfinir à chaque fois la largeur du canvas... mais ça n'est pas optimisé
    myContext.clearRect(0,0,document.documentElement.clientWidth / 2,document.documentElement.clientHeight / 2);
    
    //gérer une taille minimum pour les rectangles
    if (size <= 0) size = 1; 

    for (let i = 0; i < nbr_rect; i++) {
      myContext.fillRect(
        Math.floor(Math.random() * myCanvas.width), // x
        Math.floor(Math.random() * myCanvas.height), // y
        size, // largeur
        size // hauteur
      );
    }
    reqanimationreference = requestAnimationFrame(draw_2D);
  }, 1000 / fps); // en millisecondes
}

// 1ère frame
reqanimationreference = requestAnimationFrame(draw_2D);

// gestion du clic sur le canvas
$("#Canva2D").click(() => {
  animate = !animate;
  if (!animate) {
    cancelAnimationFrame(reqanimationreference);
    //stopper le timeout pour que l'animation ne continue pas
    clearTimeout(timer);
  } else {
    reqanimationreference = requestAnimationFrame(draw_2D);
  }
});

// gestion des touches clavier
function logKey(e) {
  switch (e.code) {
    case "NumpadAdd":
      e.preventDefault();
      size += 10;
      break;
    case "NumpadSubtract":
        e.preventDefault();
      size -= 10;
      break;
  }
}
document.addEventListener("keydown", logKey);

// gestion du clic droit
document.addEventListener("contextmenu", function(e) {
  e.preventDefault(); // empêcher le clic droit de remonter (bubbling) et afficher le menu contextuel
  let red = Math.floor(Math.random() * 256); // [0,255]
  let green = Math.floor(Math.random() * 256);
  let blue = Math.floor(Math.random() * 256);
  myContext.fillStyle = "rgba(" + red + "," + green + "," + blue + ",1)";
});

// pour dessiner d'autres formes :
// https://developer.mozilla.org/fr/docs/Tutoriel_canvas/Formes_g%C3%A9om%C3%A9triques
