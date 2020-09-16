// Doc intéressante sur le DOM : https://la-cascade.io/le-dom-cest-quoi-exactement/?fbclid=IwAR12uAqIdocw1oljAqO4I-G27lUYFxueGloHgJE5LaY27GXldLEuUF3ubeo
// Utiliser du JS à la place du Jquery : https://stackoverflow.com/questions/9899372/pure-javascript-equivalent-of-jquerys-ready-how-to-call-a-function-when-t?fbclid=IwAR10wiKiPjtdtwZC8GUk6HW89cXlitrjvDKrm1-JulD2fWmm2WS2dLDGJHM

/**
 * fonction qui génère un tableau 2D avec la chaine passer en paramètre 
 * @param {*} line 
 * @param {*} column 
 * @param {*} chaine 
 */
function generate2DArray (line, column, chaine) {
    var myTab = new Array(line);

    for (var i = 0; i < line; i++) {
        myTab[i] = new Array(column);
    }

    // mettre des élément à l'intérieur
    for (var i = 0; i< line; i++) {
        for (var j = 0; j < column; j++) {
            myTab[i][j] = chaine + "[" + i + "]" + "[" + j + "]";
        }
    }

    console.log(myTab);
    console.log('fin');
}


// S'assurer que le DOM est bien chargé avant l'utilisation de Jquery
$(document)


// ajout listener sur le boutton
document.getElementById("btn").addEventListener("click", generate2DArray(document.getElementById("line"), ));



/*
function myFunction() {
    document.getElementById("demo").innerHTML = "Hello World";
    console.log("hhhe");
}
*/
//generate2DArray(5,5,"CELL");