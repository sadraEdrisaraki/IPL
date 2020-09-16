package com.example.recapapp;

import android.app.Application;

import com.example.recapapp.models.MentalIPLModel;
import com.example.recapapp.models.domaine.Calcul;
import com.example.recapapp.models.domaine.Configuration;

/**
 * Class qui crée les instances de mon modèle, pour ne pas devoir recréer les models à chaque
 * "activité"
 */
public class Builder extends Application {

    MentalIPLModel mentalIPLModel;

    @Override
    public void onCreate() {
        super.onCreate();
        mentalIPLModel = new MentalIPLModel();
    }

    public MentalIPLModel getMentalIPLModel() {
        return mentalIPLModel;
    }
}
