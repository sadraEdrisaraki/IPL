package com.example.recapapp.models;

public interface ObserverPartie {
    /**
     * Méthode appelé par le modèle, quand une donnée à été mis à jour. Il l'appel pour mettre à
     * jour son/ses observers donc indirectement ses vues
     */
    void notifyDataChange();
}
