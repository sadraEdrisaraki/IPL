package com.example.recapapp.views;

import android.content.Intent;
import android.os.Build;
import android.os.Bundle;

import com.example.recapapp.Builder;
import com.example.recapapp.models.MentalIPLModel;
import com.example.recapapp.R;

import androidx.annotation.RequiresApi;
import androidx.appcompat.app.AppCompatActivity;

import android.util.Log;
import android.view.View;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.CheckBox;
import android.widget.EditText;

/**
 * Fait office de controleur et de vue en même temps.
 */
public class MainActivity extends AppCompatActivity{

    private MentalIPLModel mentalIPLModel;

    private EditText inputNbCalculs;
    private CheckBox addition;
    private CheckBox soustraction;
    private EditText inputEmail;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        /* Widgets*/
        inputNbCalculs = findViewById(R.id.nbCalculsInput);
        addition = findViewById(R.id.CheckBoxAddition);
        soustraction = findViewById(R.id.checkBoxSoustraction);
        inputEmail = findViewById(R.id.editTextEmail);

        // Recupère l'instance du Model
        mentalIPLModel = ((Builder) getApplication()).getMentalIPLModel();
    }

    /* Méthode appelé juste avant le onDestroy, Restore les attributs grâce au Bundle*/
    @Override
    protected void onSaveInstanceState(Bundle outState) {
        super.onSaveInstanceState(outState);
    }

    /* Méthode appelé juste avant le onStart, Restore les attributs grâce au Bundle*/
    @Override
    protected void onRestoreInstanceState(Bundle savedInstanceState) {
        super.onRestoreInstanceState(savedInstanceState);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_configuration) {
            Intent intent = new Intent(this, ConfigurationActivity.class);
            startActivity(intent);
        }
        return super.onOptionsItemSelected(item);
    }

    @RequiresApi(api = Build.VERSION_CODES.N)
    public void onClicNewGame(View view) {

        // Set le model
        mentalIPLModel.setEmail(inputEmail.getText().toString());
        mentalIPLModel.initialiser(addition.isChecked(), soustraction.isChecked(), Integer.parseInt(inputNbCalculs.getText().toString()));

        Log.d("MainActivity : EMAIL=", inputEmail.getText().toString());
        Log.d("MainActivity", "Demande de démarrage de l'activité Partie");
        Intent intent = new Intent(this, GameActivity.class);
        startActivity(intent);
    }
}
