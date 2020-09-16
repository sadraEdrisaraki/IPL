"use strict";
var nbr_rect = 101;

// call the callback to draw our animation when the browser is ready
requestAnimationFrame(draw_2D);

function draw_2D() {
  var myCanva = document.querySelector("canvas");
  var myContext = myCanva.getContext("2d");

  //get dimensions of browser to get a full screen animation
  var browser_width = document.documentElement.clientWidth;
  var browser_height = document.documentElement.clientHeight;

  myCanva.width = browser_width;
  myCanva.height = browser_height;

  myContext.fillStyle = "blue"; //'rgba(255,0,0,0.5)';//'blue';

  //draw dynamically the rectangles at random locations
  for (let i = 0; i < nbr_rect; i++) {
    myContext.fillRect(
      Math.floor(Math.random() * browser_width),
      Math.floor(Math.random() * browser_height),
      20,
      20
    );
  }
    // Refresh automatically the animation via this recursive call :
    //requestAnimationFrame(draw_2D);
    
    // Slow the animation down via setTimeout
    //requestAnimationFrame(setTimeout(draw_2D,5000));
}


