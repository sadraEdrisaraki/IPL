package com.example.mycalc;

import android.util.Log;

import java.text.DecimalFormat;
import java.util.ArrayList;

/**
 * Le modèle de la calculatrice.
 */
public class CalcModel {

    public enum Etat{
        DEBUT, OP1, OP2, OPERATEUR, RESULTAT
    }

    private ArrayList<ObserverCalc> calcsObservers; // Vues qui observe le modèle

    private String operandeGauche;
    private String operandeDroite;
    private String operateur;
    private Etat etatCourrant;
    private DecimalFormat format = new DecimalFormat("0.#####");

    CalcModel(){
        this.operandeGauche = "0";
        this.operandeDroite = "";
        this.operateur = "";
        this.etatCourrant = Etat.DEBUT;
        this.calcsObservers = new ArrayList<>();
    }

    public void registerObserver(ObserverCalc observer) {
        calcsObservers.add(observer);
    }
    public void unregisterObserver(ObserverCalc observer) {
        calcsObservers.remove(observer);
    }

    /**
     * Notifie tous les observers
     */
    public void notifyObservers() {
        for (int i = 0; i < calcsObservers.size(); i++) {
            calcsObservers.get(i).makeChangebyNotify();
        }
    }

    public void reset() {
        this.operandeGauche = "0";
        this.operandeDroite = "";
        this.operateur = "";
        this.etatCourrant = Etat.DEBUT;
    }

    /**
     * Ajout d'une operande soit à gauche soit à droite de l'opération en fonction de l'état dans lequel
     * on est
     * @param chiffre   le chiffre qu'on veut ajouter à l'opérande
     */
    public void addOperande(String chiffre) {

        switch (etatCourrant) {
            case DEBUT:
                operandeGauche = chiffre;
                etatCourrant = Etat.OP1;
                break;
            case OP1:
                operandeGauche += chiffre;
                break;
            case OPERATEUR:
                operandeDroite = chiffre;
                etatCourrant = Etat.OP2;
                break;
            case OP2:
                operandeDroite += chiffre;
                break;
            case RESULTAT:
                reset();
                operandeGauche = chiffre;
                etatCourrant = Etat.OP1;

        }
        notifyObservers();
    }

    /**
     * Méthode qui réagit quand on rentre un operateur en fontion de l'état dans lequel on est.
     * @param operateur     L'operateur qu'on ajoute à l'opération
     */
    public void addOperateur(String operateur) {

        switch (etatCourrant) {

            case OP1:
                this.operateur = operateur;
                etatCourrant = Etat.OPERATEUR;
                break;
            case OP2:
                this.result();
            case RESULTAT:
                this.operateur = operateur;
                etatCourrant = Etat.OPERATEUR;
                break;
            case OPERATEUR:
                this.operateur = operateur;
                break;
        }

        notifyObservers();
    }

    public void resetCurrentOperande() {
        switch (etatCourrant) {
            case DEBUT:
            case RESULTAT:
            case OP1:
                this.operandeGauche = "0";
                break;
            default:
                this.operandeDroite = "0";
                break;
        }
        notifyObservers();
    }

    public void resetAllOperation() {
        this.reset();
        notifyObservers();
    }

    /**
     * Supprime petit à petit l'opérande en cours
     */
    public void deleteOperande() {
        switch(etatCourrant) {
            case OP1:
                this.operandeGauche = this.operandeGauche.substring(0, this.operandeGauche.length()-1);
                break;
            case OP2:
                this.operandeDroite = this.operandeDroite.substring(0, this.operandeDroite.length()-1);
                break;
        }
        notifyObservers();
    }

    public void result() {

        if(!operandeDroite.equals("") && !operandeGauche.equals("") && !operateur.equals("")) {
            etatCourrant = Etat.RESULTAT;
            Double res = calculate();
            format.format(res);
            Log.d("Model", "Resultat de l'opération " + format.format(res));

            this.setOperandeGauche(format.format(res));
            this.setOperandeDroite("");
            this.setOperateur("");

            notifyObservers();
        }
    }

    private double calculate() {
        double res = 0.0;
        switch (this.operateur) {
            case "+":
                res = Double.parseDouble(operandeGauche) + Double.parseDouble(operandeDroite);
                break;
            case "/":
                res = Double.parseDouble(operandeGauche) / Double.parseDouble(operandeDroite);
                break;
            case "*":
                res = Double.parseDouble(operandeGauche) * Double.parseDouble(operandeDroite);
                break;
            case "-":
                res = Double.parseDouble(operandeGauche) - Double.parseDouble(operandeDroite);
                break;
        }

        return res;

    }

    /**
     * Ajout un signe à l'opérande
     *
     */
    public void addSigned() {

        switch(etatCourrant) {
            case OP1:
                if (this.operandeGauche.substring(0,1).equals("-")) {
                    this.operandeGauche = this.operandeGauche.substring(1);
                } else {
                    this.operandeGauche = "-" + this.operandeGauche;
                }
                break;
            case OP2:
                if (this.operandeDroite.substring(0,1).equals("-")) {
                    this.operandeDroite = this.operandeDroite.substring(1);
                } else {
                    this.operandeDroite = "-" + this.operandeDroite;
                }
                break;
        }
        notifyObservers();
    }

    public String getOperandeGauche() {
        return this.operandeGauche;
    }

    public String getOperandeDroite() {
        return this.operandeDroite;
    }

    public String getOperateur() {
        return this.operateur;
    }

    public void setOperandeGauche(String newValue) {
        this.operandeGauche = newValue;
    }

    public void setOperandeDroite(String newValue) {
        this.operandeDroite = newValue;
    }

    public void setOperateur(String newValue) {
        this.operateur = newValue;
    }

    public Etat getEtat() {
        return etatCourrant;
    }


}
