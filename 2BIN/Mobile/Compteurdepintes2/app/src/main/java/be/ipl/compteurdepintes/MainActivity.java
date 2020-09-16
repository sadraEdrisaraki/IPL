package be.ipl.compteurdepintes;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.os.Bundle;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.text.InputType;
import android.util.Log;
import android.view.View;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    private final String MAX_PINTES = "Max_Pintes";

    private final int REQUEST_HIGHSCORE = 1;

    private final int REQUEST_PANIC = 2;

    private final String HIGHSCORE_STRING = "HighScore";

    private Integer compteurTotalDeBiere;

    private Integer highScore;

    private TextView textView_compteur;

    private TextView textView_commente;

    private TextView textView_HighScore;

    private String currentCommente;

    private Integer max_pintes;

    private Boolean alreadyGoToHighScoreScreen;

    private Integer phone_number;

    private SharedPreferences pref;

    private Button button_compteur;


    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        pref = getApplicationContext().getSharedPreferences(HIGHSCORE_STRING, 0);

        highScore = pref.getInt(HIGHSCORE_STRING, 0);

        // Si c'est la première fois qu'on lance l'app
        if (savedInstanceState == null) {
            compteurTotalDeBiere = 0;
            max_pintes = 0;
            alreadyGoToHighScoreScreen = false;
        }

        button_compteur = (Button) findViewById(R.id.button_compteur);
        button_compteur.setText(R.string.buttonCompteur);

        textView_compteur = (TextView) findViewById(R.id.textView_compteur);
        textView_commente = (TextView) findViewById(R.id.textView_commentaire);

        textView_HighScore = (TextView) findViewById(R.id.textView_highScore);
        textView_HighScore.setText(R.string.HighScore_label);
        textView_HighScore.append(highScore.toString());
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement

        switch (id) {
            case R.id.quitter_partie:
                this.finish();
                break;
            case R.id.recommencer_partie:
                // changer : remettre les variables à 0 au lieu de kill
                Intent intent = getIntent();
                finish();
                startActivity(intent);
            case R.id.configurer_numero:
                configurationNumero();
        }

        return super.onOptionsItemSelected(item);
    }

    public void onUpdateCommente (View view) {

        compteurTotalDeBiere += 1;
        textView_compteur.setText(compteurTotalDeBiere.toString());

        switch (compteurTotalDeBiere) {
            case 1:
                currentCommente = getResources().getString(R.string.txt_1);
                break;
            case 5:
                currentCommente = getResources().getString(R.string.txt_5);
                break;
            case 8:
                currentCommente = getResources().getString(R.string.txt_8);
                break;
            case 10:
                currentCommente = getResources().getString(R.string.txt_10);
                break;
            case 12:
                currentCommente = getResources().getString(R.string.txt_12);
                break;
            case 15:
                currentCommente = getResources().getString(R.string.txt_15);
                break;
            case 18:
                currentCommente = getResources().getString(R.string.txt_18);
                break;
            case 24:
                currentCommente = getResources().getString(R.string.txt_24);
                break;
            case 30:
                currentCommente = getResources().getString(R.string.txt_30);
                break;
            case 50:
                currentCommente = getResources().getString(R.string.txt_50);
                break;
        }

        textView_commente.setText(currentCommente); // Met à jour le commentaire


        if (compteurTotalDeBiere == max_pintes) {

            Log.d("MainActivty", "Lancement de la nouvelle activité : Panic");
            Intent intent = new Intent(this, Panic.class);
            intent.putExtra("Phone Number", phone_number); // en attendant avant de faire les shared preferences
            startActivityForResult(intent, REQUEST_PANIC);
        }

        // HighScore battu
        if (compteurTotalDeBiere > highScore) {

            highScore = compteurTotalDeBiere;

            /* Met à jours les textes */
            textView_HighScore.setText(R.string.HighScore_label);
            textView_HighScore.append(highScore.toString());

            String newStringHighScore = getResources().getString(R.string.newHighScore); // recupère le string dans le fichier ressources
            textView_commente.append(" ");
            textView_commente.append(newStringHighScore);

            if (!alreadyGoToHighScoreScreen) {
                Log.d("MainActivty", "Lancement de la nouvelle activité : HighScore");
                Intent intent = new Intent(this, HighScore.class);
                startActivityForResult(intent, REQUEST_HIGHSCORE);
            }
        }

        Log.d("Main", "Compteur de bière: " + compteurTotalDeBiere);
        Log.d("Main", "Max pintes: " + max_pintes);
    }

    /*
        Méthode appelé juste avant de mourir
     */
    @Override
    protected void onSaveInstanceState(@NonNull Bundle outState) {

        super.onSaveInstanceState(outState);

        outState.putInt("CurrentBiere", compteurTotalDeBiere);
        outState.putBoolean("alreadyGoToHighScoreScreen", alreadyGoToHighScoreScreen);
        outState.putString("currentCommente", currentCommente);
        outState.putInt("Max pintes", max_pintes);

        Log.d("Bundle", "Sauvegarde de l'état");

    }

    /*
      Méthode appelé juste avant le Onstart()
   */
    @Override
    protected void onRestoreInstanceState(Bundle savedInstanceState) {
        super.onRestoreInstanceState(savedInstanceState);
        compteurTotalDeBiere = savedInstanceState.getInt("CurrentBiere");
        alreadyGoToHighScoreScreen = savedInstanceState.getBoolean("alreadyGoToHighScoreScreen");
        currentCommente = savedInstanceState.getString("currentCommente");
        max_pintes = savedInstanceState.getInt("Max pintes");

        //
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        switch (requestCode) {
            case (REQUEST_HIGHSCORE):
                if (resultCode == Activity.RESULT_OK) {
                    max_pintes = data.getIntExtra(MAX_PINTES,0);
                    alreadyGoToHighScoreScreen = true;
                }
            case (REQUEST_PANIC):
                if (resultCode == Activity.RESULT_OK) {

                }
        }
    }

    private void configurationNumero() {
        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        builder.setTitle("Configuration du numéro");

        final EditText input = new EditText(this);

        input.setInputType(InputType.TYPE_CLASS_PHONE);
        builder.setView(input);

        builder.setPositiveButton("OK", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                phone_number = Integer.parseInt(input.getText().toString());
                // sauvegarder dans les sharedPreferences.
            }
        });

        builder.setNegativeButton("Cancel", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                dialog.cancel();
            }
        });

        builder.show();

    }
}
