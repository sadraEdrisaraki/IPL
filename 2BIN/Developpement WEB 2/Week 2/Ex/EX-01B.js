function myRedirectWithClosure(url){
    return function(){
      window.location.href = url;
    }
  }

  function myRedirect(url){

    window.location.href = url;
  }

  

$(document).ready(function() {
  //per default, hide the alertbox
  $("#message_board").hide();

  $("#btn").click(function(e) {
    // as we are dealing with a form, in order for it not to be sent as a GET HTTP form
    e.preventDefault();
    //per default, hide the alertbox
    $("#message_board").hide();
    //per default, reset the message box content :
    $("#message_board").html("<p>Error:</p>");
    //set the default input classes (Bootstrap class)
    $("input").attr("class", "form-control");
    //init a flag to check for successful operation
    let success = true;

    // check that the username is not empty
    // Optional : improve this with RegEx to check for non-word character...
    if ($("#username").val() == "") {
      // make the alert box visible
      $("#message_board").show();
      // JQuery to append a new html tag
      $("#message_board").append("<p>- Please enter a username!</p>");
      // Set the background of the input to red (via Bootstrap here)
      $("#username").addClass("bg-danger");
      success = false;
    }
    // you can learn over RegEx here : https://www.w3schools.com/jsref/jsref_obj_regexp.asp
    // you can use Regex to test your strings : https://regex101.com/
    // check that there is no number in the name
    else if (/\d/.test($("#username").val())) {
      // make the alert box visible
      $("#message_board").show();
      // JQuery to append a new html tag
      $("#message_board").append(
        "<p>- You cannot add a number in your username!</p>"
      );
      // Set the background of the input to red (via Bootstrap here)
      $("#username").addClass("bg-danger");
      //ISSUE, bootstrap CSS class not taken into account when autofill
      $("input").css("-webkit-box-shadow","0 0 0 30px red inset");
      success = false;
      
    }
    // check that the email format is OK (explanation here : https://www.w3resource.com/javascript/form/email-validation.php)
    if (
      /^\w+([\.-]?\w+)*@\w+([\.-]?\w+)*(\.\w{2,4})+$/.test(
        $("#email").val()
      ) === false
    ) {
      $("#message_board").show();
      $("#message_board").append("<p>- Please enter a valid email!</p>");
      $("#email").addClass("bg-danger");
      $("input").css("-webkit-box-shadow","0 0 0 30px red inset");
      success = false;
    }
    // check that the password format is OK
    if (/.*[A-Z]+.*/.test($("#password").val()) === false) {
      $("#message_board").show();
      $("#message_board").append(
        "<p>- Please enter a valid password (at least one uppercase letter)!</p>"
      );
      $("#password").addClass("bg-danger");
      success = false;
    }

    // if validation is successful, redirect after 2 seconds (and green inputs)
    if (success)
    {
      //ISSUE, bootstrap CSS class not taken into account when autofill
      //https://css-tricks.com/snippets/css/change-autocomplete-styles-webkit-browsers/
      //$("input").addClass("bg-success");
      $("input").css("background-color","green");
      $("input").css("-webkit-box-shadow","0 0 0 30px green inset");
      //just an example on how to pass a parameter to a callback function
      let myUrl = "https://www.123greetings.com/congratulations/";
      
      // Sol 1 : using bind method
      //setTimeout(myRedirect.bind(this,myUrl),2000);
      // Sol 2 : using closure
      //setTimeout(myRedirectWithClosure(myUrl),2000);
      // Sol 3 : using arrow function
      setTimeout(() => myRedirect(myUrl),2000);

    }
    


  });

  

});
