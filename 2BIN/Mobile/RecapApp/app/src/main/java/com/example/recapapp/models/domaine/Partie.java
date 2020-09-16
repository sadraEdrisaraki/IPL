package com.example.recapapp.models.domaine;

import android.os.Build;

import androidx.annotation.RequiresApi;

import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public class Partie {
    public static final int MAX_OPERATION_DEFAUT = 20;
    public static final int MIN_OPERATION_DEFAUT = 0;
    public static final int NB_CALCULS_DEFAUT = 5;
    public static final String MENTAL_IPL = "mentalIPL";
    /**
     * Map qui retient si les générateurs de calculs peuvent être utilisé dans la partie.
     */
    private Map<GenerateurDeCalculs, Boolean> operationMap = new HashMap<>();
    private GenerateurDeCalculs addition, soustraction;
    private Calcul calculCourant;
    private int nbCalculsTotal, nbCalculsGeneres;

    /**
     * Constructeur de Partie.
     * Par défaut, les opérations de soustraction et d'addition sont configurées pour être possible.
     */
    public Partie() {
        addition = new GenerateurDAddition(new Configuration(MIN_OPERATION_DEFAUT, MAX_OPERATION_DEFAUT));
        soustraction = new GenerateurDeSoustraction(new Configuration(MIN_OPERATION_DEFAUT, MAX_OPERATION_DEFAUT));
        this.nbCalculsTotal = NB_CALCULS_DEFAUT;
        this.operationMap.put(addition, true);
        this.operationMap.put(soustraction, true);
    }


    /**
     * Cette méthode permet de (re)initialiser une partie
     *
     * @param choixAdd  true si l'addition est autorisée, false sinon
     * @param choixSous true si la soustraction est autorisee
     * @param nbCalculs le nombre de calcul de la partie
     */
    public void reinitialiser(boolean choixAdd, boolean choixSous, int nbCalculs) {
        enregistrerAddition(choixAdd);
        enregistrerSoustraction(choixSous);
        this.nbCalculsGeneres = 0;
        this.nbCalculsTotal = nbCalculs;
    }

    public Calcul getCalculCourant() {
        return this.calculCourant;
    }


    @RequiresApi(api = Build.VERSION_CODES.N)
    public void passerAuCalculSuivant() {

        if (nbCalculsGeneres == nbCalculsTotal)
            this.calculCourant = null;
        else {
            this.calculCourant = genererCalculSuivant();
            nbCalculsGeneres++;
        }


    }

    @RequiresApi(api = Build.VERSION_CODES.N)
    private Calcul genererCalculSuivant() {
        List<GenerateurDeCalculs> operationList = operationMap.entrySet().stream().filter(e -> e.getValue() == true)
                .map(e -> e.getKey()).collect(Collectors.toList());
        int randOP = (int) (Math.random() * operationList.size());
        return operationList.get(randOP).fournirCalcul();
    }




    public int getNbCalculsTotal() {
        return nbCalculsTotal;
    }

    public int getNbCalculsGeneres() {
        return nbCalculsGeneres;
    }

    public Configuration getConfigurationAddition() {
        return addition.getConfiguration();
    }

    public Configuration getConfigurationSoustraction() {
        return soustraction.getConfiguration();
    }

    public boolean isAdditionPermis() {
        return operationMap.get(addition);
    }

    public boolean isSoustractionPermis() {
        return operationMap.get(soustraction);
    }

    private void enregistrerAddition(boolean add) {
        this.operationMap.put(addition, add);
    }

    private void enregistrerSoustraction(boolean sous) {
        this.operationMap.put(soustraction, sous);
    }

}
