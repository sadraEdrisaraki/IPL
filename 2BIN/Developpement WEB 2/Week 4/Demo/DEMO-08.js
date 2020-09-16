$(document).ready(function () {
    //per default, hide the alertbox
    $("#message_board").hide();

    $("#btn").click(function (e) {
        // as we are dealing with a form, in order for it not to be sent as a GET HTTP form
        try {
            e.preventDefault();

            //per default, hide the alertbox
            $("#message_board").hide();
            //per default, reset the message box content :
            $("#message_board").html("<p>Error:</p>");
            //set the default input classes (Bootstrap class)
            $("input").attr("class", "form-control");
            validateLoginForm();
        } catch (err) {
            $("#message_board").show();
            // err is an array. Loop through this array
            err.forEach(element => {
                $("#message_board").append("<p>- " + element.message + "</p>");
            });

        }
    });
});

function validateLoginForm(email, password) {
    // check that the email format is OK (explanation here : https://www.w3resource.com/javascript/form/email-validation.php)
    // create an empty array to collect all potential errors
    var errors = [];
    if ($("#email").val() == "") {
        // add an error to the array
        errors.push(new Error("No email"));
    } else if (
        /^\w+([\.-]?\w+)*@\w+([\.-]?\w+)*(\.\w{2,4})+$/.test($("#email").val()) ===
        false
    ) {
        // add an error to the array
        errors.push(new Error("Invalid email format"));
    }
    // check that the password format is OK
    if ($("#password").val() == "") {
        // add an error to the array
        errors.push(new Error("No password"));
    }
    else if (/.*[A-Z]+.*/.test($("#password").val()) === false) {
        errors.push(new Error("Invalid password format"));
    }
    if (errors.length !== 0)
        throw errors;
    else
        return { success: true };
}