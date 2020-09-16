"use strict";


var animation = anime({
    //here you specify your targeted element through CSS selector syntax
    targets: '#propeller',
    rotate: '360',
    //duration in ms to make one iteration
    duration: 1000,
    //number of iterations or true for indefinitely
    loop: true,
    //don't start automatically the animation
    autoplay: false,
    easing: 'linear'
});

$("document").ready(function () {
    // get(0) retrieve the 1st element found by the JQuerySelector
    //mouseenter event is more convenient than mouseover in order not to restart the animation spuriously after a click
    $("#propeller").get(0).addEventListener("mouseenter", function () {
        // start the animation 
        console.log(anime.running.length);
        animation.play();
    });

    $("#propeller").get(0).addEventListener("click", function (e) {
        // pause the rotation animation
        animation.pause();
        // inflate our propeller

        anime({
            //here you specify your targeted element through CSS selector syntax
            targets: '#propeller',
            scale: '360',
            //duration in ms to make one iteration
            duration: 1000,
            scale: 2,
            //start automatically the animation
            autoplay: true,
            //to go from scale x2 back and forth
            direction:"alternate",
            //number of iterations or true for indefinitely
            loop:true,
            easing: 'linear'
        });

    });


    document.addEventListener("keydown", function (e) {
        //for the sake of the demo, we have used a simple animation to create a propeller
        //keyboard codes can be found here : https://developer.mozilla.org/en-US/docs/Web/API/KeyboardEvent/code
        if (e.code === 'ArrowUp') {            
            //the animation to go up has to be inside in the click event in order to start from a relative correct position
            //if the animation is declared globally, it will always start to translate from the same position

            //don't start the animation if no other animation is running
            if (anime.running.length != 0 ) {
                anime({
                    targets: '#lift',
                    translateY: '-=50',
                    //duration in ms to make one iteration
                    duration: 1000,
                    autoplay: true,
                    easing: 'linear'
                });
            }
        }

        if (e.code === 'ArrowDown') {
            //e.preventDefault();  // stop default action
            //the animation to go up has to be inside in the click event in order to start from a relative correct position
            //if the animation is declared globally, it will always start to translate from the same position
            if (anime.running.length != 0) {
                anime({
                    targets: '#lift',
                    translateY: '+=50',
                    //duration in ms to make one iteration
                    duration: 1000,
                    autoplay: true,
                    easing: 'linear'
                });
            }
        }

    });
})