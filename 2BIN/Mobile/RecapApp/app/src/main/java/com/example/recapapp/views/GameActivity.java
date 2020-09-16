package com.example.recapapp.views;

import android.content.Intent;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ProgressBar;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.annotation.RequiresApi;
import androidx.appcompat.app.AppCompatActivity;

import com.example.recapapp.Builder;
import com.example.recapapp.R;
import com.example.recapapp.models.MentalIPLModel;
import com.example.recapapp.models.ObserverPartie;

public class GameActivity extends AppCompatActivity implements ObserverPartie {

    private MentalIPLModel mentalIPLModel;

    // Widgets
    private TextView calculPrecedent;
    private TextView calculCourant;
    private EditText reponse;
    private Button valideCalcul;
    private ProgressBar progressBar;
    private TextView nbCalculsEffectue;
    private TextView textViewCalcule;


    @RequiresApi(api = Build.VERSION_CODES.N)
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.game_activity);

        // Recupère l'instance du Model
        mentalIPLModel = ((Builder) getApplication()).getMentalIPLModel();

        // Init les widgets
        calculPrecedent = findViewById(R.id.textViewHistorique);
        calculCourant = findViewById(R.id.textViewCalculCourrant);
        reponse = findViewById(R.id.editTextReponse);
        valideCalcul = findViewById(R.id.buttonValide);
        progressBar = findViewById(R.id.progressBarNbCalcules);
        nbCalculsEffectue = findViewById(R.id.textViewNbCalculs);
        textViewCalcule = findViewById(R.id.textViewCalcule);

        progressBar.setMax(mentalIPLModel.getMaxCalculs());
        // init le premier calcul
        calculCourant.setText(mentalIPLModel.fournirCalcul().getCalcul());

        // listener bouton "OK"
        valideCalcul.setOnClickListener(
                view -> {
                    if (mentalIPLModel.estTermine()) {
                        mentalIPLModel.setRapport();
                        sendRapport();
                    } else{
                        mentalIPLModel.enregistrerResultat(Double.parseDouble(reponse.getText().toString()));
                    }
                });
    }

    @Override
    public void notifyDataChange() {
        calculPrecedent.setText(mentalIPLModel.getCalculPrecedent());
        progressBar.setProgress(mentalIPLModel.nombreCalculsFaits());
        String commentaire = mentalIPLModel.nombreCalculsFaits() + " "+getResources().getString(R.string.nbCalculsEffectue);
        nbCalculsEffectue.setText(commentaire);
        // Bonne réponse ou pas ?
        if (mentalIPLModel.aBienRepondu()) {
            calculPrecedent.setTextColor(getColor(R.color.colorGreen));
        } else {
            calculPrecedent.setTextColor(getColor(R.color.colorRed));
        }
        reponse.setText("");
        //Partie terminée ou pas ?
        if (mentalIPLModel.estTermine()) {
            reponse.setVisibility(View.GONE);
            textViewCalcule.setText(R.string.endGame);
            calculCourant.setText("");
        } else {
            calculCourant.setText(mentalIPLModel.fournirCalcul().getCalcul());
        }
    }

    /* Ajoute l'observer au model quand l'app à start */
    @Override
    protected void onStart() {
        super.onStart();
        mentalIPLModel.registerObserver(this);
    }

    /* Supprimer l'observer du model quand l'app est stopper*/
    @Override
    protected void onStop() {
        super.onStop();
        mentalIPLModel.unregisterObserver(this);
    }

    public void sendRapport() {
        Log.d("Partie Activity", "Envoie du rapport ");
        Intent emailIntent = new Intent(Intent.ACTION_SEND);
        emailIntent.setData(Uri.parse("mailto:"));
        emailIntent.setType("text/plain");
        String[] TO = {mentalIPLModel.getEmail()};
        emailIntent.putExtra(Intent.EXTRA_EMAIL,TO );
        emailIntent.putExtra(Intent.EXTRA_SUBJECT, "Rapport MentalIPL");
        emailIntent.putExtra(Intent.EXTRA_TEXT, mentalIPLModel.getRapport());
        startActivity(Intent.createChooser(emailIntent, "send email"));
        finish();
    }


    @Override
    protected void onRestoreInstanceState(@NonNull Bundle savedInstanceState) {
        super.onRestoreInstanceState(savedInstanceState);
        calculPrecedent.setText(mentalIPLModel.getCalculPrecedent());
        if (mentalIPLModel.aBienRepondu()) {
            calculPrecedent.setTextColor(getColor(R.color.colorGreen));
        } else {
            calculPrecedent.setTextColor(getColor(R.color.colorRed));
        }
        String commentaire = mentalIPLModel.nombreCalculsFaits() + " "+getResources().getString(R.string.nbCalculsEffectue);
        nbCalculsEffectue.setText(commentaire);
    }
}
