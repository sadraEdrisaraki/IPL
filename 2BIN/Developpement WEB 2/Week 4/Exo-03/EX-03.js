"use strict";

const libraries = [
  "Anime.js",
  "Three.js",
  "Phaser.io",
  "GSAP",
  "Mo.js",
  "Velocity",
  "..."
];

let root = document.getElementById("root");
//get dimensions of browser to get a full screen animation
let browser_width = document.documentElement.clientWidth;
let browser_height = document.documentElement.clientHeight;

for (let i = 0; i < libraries.length; i++) {
  let word = document.createElement("div");
  word.innerText = libraries[i];
  word.className = "word d-inline-block";
  root.appendChild(word);
}
let animation;
let scaleAnimations = [];

randomMove();

function randomMove() {
  animation = anime({
    //animationTimeline.add({
    //here you specify your targeted element through CSS selector syntax
    targets: ".word", //propeller,
    translateX: {
      value: function(target, index, targetsLength) {
        // get x position
        let current_x = target.getBoundingClientRect().left;
        let random_x = anime.random(0, browser_width - current_x);

        return random_x;
      },
      duration: 3000
    },
    translateY: {
      value: function(target, index, targetsLength) {
        let current_y = target.getBoundingClientRect().top;
        let random_y = anime.random(0, browser_height - current_y);

        return random_y;
      },
      duration: 3000
    },
    //duration in ms to make one iteration
    //duration: 3000,
    easing: "linear",
    //number of iterations or true for indefinitely
    complete: randomMove
  });
}

document.querySelectorAll(".word").forEach(item => {
  item.addEventListener("mouseenter", event => {
    //don't try again to animate if it is already running
    //animation.pause();
    if (event.target.className.search(/mouseentered|clicked/i) < 0)
      scaleAnimations.push(
        anime({
          //here you specify your targeted element through CSS selector syntax
          targets: event.target,
          //duration in ms to make one iteration
          duration: 1000,
          scale: 3,
          //start automatically the animation
          //autoplay: true,
          //to go from scale x2 back and forth
          direction: "alternate",
          //number of iterations or true for indefinitely
          loop: true,
          easing: "linear"
        })
      );
    //stop the animation only for the selected element (remove "word" class)
    event.target.className = "mouseentered d-inline-block";
  });
});

document.querySelectorAll(".word").forEach(item => {
  item.addEventListener("click", event => {
    //stop the main animation
    console.log("clicked");
    animation.pause();
    //inflateAnimation.pause();
    scaleAnimations.forEach(item => {
      item.pause();
    });
    //hide all elements but not the one clicked
    event.target.className = "clicked d-inline-block";

    document.querySelectorAll(".word,.mouseentered").forEach(item => {
      //don't remove item from the DOM as the DIV would move from position
      //item.remove()
      //ditto, don't hide the elements as the final word would move from position
      //item.className = "d-none";
      //bootstrap invisible class does not affect layout : )
      item.className = "invisible d-inline-block";
    });
    //show the modal with the word of the day
    //prepare the word of the day in the modal
    document.getElementById("message").innerText = event.target.innerText;
    $("#exampleModal").modal("show");

    anime({
      //here you specify your targeted element through CSS selector syntax
      targets: event.target,
      //duration in ms to make one iteration
      scale: {
        value: 5,
        easing: "linear",
        duration: 2000
      },
      rotate: {
        value: "360",
        easing: "linear",
        duration: 2000
      },
      loop: 4,
      direction: "alternate"
    });
  });
});
