package com.example.recapapp.models;

import android.os.Build;
import android.util.Log;

import androidx.annotation.RequiresApi;

import com.example.recapapp.models.domaine.Calcul;
import com.example.recapapp.models.domaine.Partie;

import java.util.ArrayList;

public class MentalIPLModel {

    private Partie partie;
    private ArrayList<ObserverPartie> observers = new ArrayList<>();
    private ArrayList<String> calculsErrones = new ArrayList<>();

    private String calculCourant, calculPrecedent = "";
    private boolean bienRepondu = true;
    private int nbBonnesReponses, nbReponses;

    private String email= "";
    private String rapport = "";

    public MentalIPLModel() {
        partie = new Partie();
    }

    public void registerObserver(ObserverPartie observer) {
        observers.add(observer);
    }

    public void unregisterObserver(ObserverPartie observer) {
        observers.remove(observer);
    }

    @RequiresApi(api = Build.VERSION_CODES.N)
    public void initialiser(boolean add, boolean sous, int nbOperations) {
        partie.reinitialiser(add, sous, nbOperations);
        nbBonnesReponses = 0;
        nbReponses = 0;
        rapport = "";
        partie.passerAuCalculSuivant();
        rapport += "Rapport de partie de calcul mental\n";
        rapport += nbOperations + " calculs effectuées - \n";
        rapport += "Résultat: ";
    }

    public Calcul fournirCalcul() {
        return partie.getCalculCourant();
    }

    private void notifyObservers() {
        for (ObserverPartie observer : observers) {
            observer.notifyDataChange();
        }
    }

    @RequiresApi(api = Build.VERSION_CODES.N)
    public void enregistrerResultat(double proposition) {
        calculPrecedent = partie.getCalculCourant().getCalcul() + proposition;
        nbReponses += 1;
        if (partie.getCalculCourant().getRes() == proposition) {
            bienRepondu = true;
            nbBonnesReponses += 1;
         } else {
            bienRepondu = false;
            calculPrecedent += "(" + partie.getCalculCourant().getRes() +")";
            calculsErrones.add(calculPrecedent);
        }

        partie.passerAuCalculSuivant();
        notifyObservers();
    }

    public boolean aBienRepondu() {
        return bienRepondu;
    }

    public String getCalculPrecedent() {
        return calculPrecedent;
    }

    public boolean estTermine() {
        return nbReponses == partie.getNbCalculsTotal();
    }

    public int nombreCalculsFaits() {
        return nbReponses;
    }

    public int getConfigurationSoustractionMin() {
        return partie.getConfigurationSoustraction().getMin();
    }

    public int getConfigurationSoustractionMax() {
        return partie.getConfigurationSoustraction().getMax();
    }

    public int getConfigurationAdditionMin() {
        return partie.getConfigurationAddition().getMin();
    }

    public int getConfigurationAdditionMax() {
        return partie.getConfigurationAddition().getMax();
    }

    public void changerMinAddition(int min) {
        partie.getConfigurationSoustraction().setMin(min);
    }

    public void changerMaxAddition(int max) {
        partie.getConfigurationAddition().setMax(max);
    }

    public void changerMinSoustraction(int min) {
        partie.getConfigurationSoustraction().setMin(min);
    }

    public void changerMaxSoustraction(int max){
        partie.getConfigurationSoustraction().setMax(max);
    }

    public void setEmail(String Email) {
        email = Email;
    }

    public String getEmail() {
        Log.d("l'email vaut=", email);
        return email;
    }

    public String getRapport() {
        return rapport;
    }

    public int getMaxCalculs() {
        return partie.getNbCalculsTotal();
    }

    public void setRapport() {
        float percent = (nbBonnesReponses * 100.0f) /nbReponses;
        rapport += percent + "\n";
        rapport += "Liste de calculs erronés \n";
        for(String calcul : calculsErrones) {
            rapport += calcul +"\n";
        }

    }

}
