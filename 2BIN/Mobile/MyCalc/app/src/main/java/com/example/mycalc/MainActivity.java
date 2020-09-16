package com.example.mycalc;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.os.PersistableBundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import java.text.BreakIterator;
import java.text.DecimalFormat;


public class MainActivity extends AppCompatActivity implements ObserverCalc {

    private TextView affichageResultat;
    private CalcModel maCalculatrice;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        /* Initialisation des widgets */
        affichageResultat = findViewById(R.id.affichage);

        maCalculatrice = ((Builder) getApplication()).getModelCalc();
    }

    @Override
    protected void onStart() {
        super.onStart();
        maCalculatrice.registerObserver(this); // Après que l'activité ait start on enregistre l'observer.
    }

    @Override
    protected void onStop() {
        super.onStop();
        maCalculatrice.unregisterObserver(this); // Si l'activité est stop on désenregistre l'observer.
        // Y a t'il une raison particulière à désenregistrer l'observer ?
    }

    @Override
    public void onSaveInstanceState(Bundle outState, PersistableBundle outPersistentState) {
        super.onSaveInstanceState(outState, outPersistentState);
    }

    /* Méthode appelé juste avant le onStart, Restore les attributs grâce au Bundle*/
    @Override
    protected void onRestoreInstanceState(Bundle savedInstanceState) {

        super.onRestoreInstanceState(savedInstanceState);
    }

    @Override
    public void makeChangebyNotify() {
        /* Met à jour la vue*/
        String affichage = maCalculatrice.getOperandeGauche()
                + maCalculatrice.getOperateur()
                + maCalculatrice.getOperandeDroite();

        Log.d("MainActivity", "Opération en cours= " + affichage + " ,etat courant=" + maCalculatrice.getEtat());
        affichageResultat.setText(affichage);
    }

    // Quand on clic sur un nombre
    public void onNumber(View view) {
        maCalculatrice.addOperande(view.getTag().toString());
    }

    // Quand on clic sur un operateur
    public void onOperateur(View view) {
        maCalculatrice.addOperateur(view.getTag().toString());
    }

    // Quand on clic sur le =
    public void onResult(View view) {
        Log.d("MainActivty", "Lancement du résultat");
        maCalculatrice.result();
    }

    // Quand on clic sur le CE
    public void onResetCurrentNumber(View view) {
        Log.d("MainActivty", "Suppression de l'opérande en cours");
        maCalculatrice.resetCurrentOperande();
    }

    // Quand on clic sur le C
    public void onResetAll(View view) {
        Log.d("MainActivty", "Suppression de toute l'opération en cours");
        maCalculatrice.resetAllOperation();
    }

    // Quand on clic sur SUPP, supprime le dernier chiffre
    public void onDeleteOp(View view) {
        Log.d("MainActivty", "Suppression du dernier chiffre de l'opérande en cours");
        maCalculatrice.deleteOperande();
    }

    public void onAddSigned(View view) {
        Log.d("MainActivity", "Ajout un signe devant le nombre");
        maCalculatrice.addSigned();
    }
}
