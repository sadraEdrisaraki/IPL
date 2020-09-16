package com.example.mycalc;

import android.app.Application;

public class Builder extends Application {

    CalcModel maCalculatrice;

    @Override
    public void onCreate() {
        super.onCreate();
        maCalculatrice = new CalcModel();
    }

    public CalcModel getModelCalc() {
        return maCalculatrice;
    }


}
