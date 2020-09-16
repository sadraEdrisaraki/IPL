package com.example.recapapp.models.domaine;

public abstract class GenerateurDeCalculs {


    private final Configuration configuration;



    public GenerateurDeCalculs(Configuration configuration) {
        this.configuration = configuration;
    }

    public Configuration getConfiguration() {
        return configuration;
    }



    abstract public Calcul fournirCalcul();




}
