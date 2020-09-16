package com.example.recapapp.views;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import com.example.recapapp.Builder;
import com.example.recapapp.R;
import com.example.recapapp.models.MentalIPLModel;

public class ConfigurationActivity extends AppCompatActivity {

    private MentalIPLModel mentalIPLModel;

    private Button borneMinAdd;
    private Button borneMaxAdd;
    private Button borneMinSous;
    private Button borneMaxSous;
    private EditText borneMinAddText;
    private EditText borneMaxAddText;
    private EditText borneMinSousText;
    private EditText borneMaxSousText;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.configuration);
        Log.d("Configuration Activity", "Demarrage de l'activité de configuration");

        //Init Widgets
        borneMinAdd = findViewById(R.id.buttonBorneMinAdd);
        borneMaxAdd =  findViewById(R.id.buttonBorneMaxAdd);
        borneMinSous = findViewById(R.id.buttonBorneMinSous);
        borneMaxSous = findViewById(R.id.buttonBorneMaxSous);

        borneMinAddText = findViewById(R.id.editTextBorneMinAdd);
        borneMaxAddText = findViewById(R.id.editTextBorneMaxAdd);
        borneMinSousText = findViewById(R.id.editTextBorneMinSous);
        borneMaxSousText = findViewById(R.id.editTextBorneMaxSous);

        // Recupère l'instance du Model
        mentalIPLModel = ((Builder) getApplication()).getMentalIPLModel();

        //Set
        borneMaxAddText.setText(Integer.toString(mentalIPLModel.getConfigurationAdditionMax()));
        borneMinAddText.setText(Integer.toString(mentalIPLModel.getConfigurationAdditionMin()));
        borneMaxSousText.setText(Integer.toString(mentalIPLModel.getConfigurationSoustractionMax()));
        borneMinSousText.setText(Integer.toString(mentalIPLModel.getConfigurationSoustractionMin()));

        // Set le model
        borneMinAdd.setOnClickListener(view -> mentalIPLModel.changerMinAddition(Integer.parseInt(borneMinAddText.getText().toString())));
        borneMaxAdd.setOnClickListener(view -> mentalIPLModel.changerMaxAddition(Integer.parseInt(borneMaxAddText.getText().toString())));
        borneMinSous.setOnClickListener(view -> mentalIPLModel.changerMinSoustraction(Integer.parseInt(borneMinSousText.getText().toString())));
        borneMaxSous.setOnClickListener(view -> mentalIPLModel.changerMaxSoustraction(Integer.parseInt(borneMaxSousText.getText().toString())));

        Log.d("Après setter", Integer.toString(mentalIPLModel.getConfigurationAdditionMax()));

    }
}
