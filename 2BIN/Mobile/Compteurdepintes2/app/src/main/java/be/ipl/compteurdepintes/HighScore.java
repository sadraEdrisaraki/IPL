package be.ipl.compteurdepintes;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

import androidx.appcompat.app.AppCompatActivity;

public class HighScore extends AppCompatActivity {

    private final String MAX_PINTES = "Max_Pintes";

    private Button button_close;

    private EditText input_max_pintes;

    private View.OnClickListener button_closeListener = new View.OnClickListener() {
        @Override
        public void onClick(View v) {

            // tant qu'il n'a pas rentrer de nombre
            if(input_max_pintes.getText().toString().length() != 0) {
                Intent intent = new Intent();
                intent.putExtra(MAX_PINTES, Integer.parseInt(input_max_pintes.getText().toString()));
                setResult(Activity.RESULT_OK, intent);
                finish();
            }

        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {

        Log.d("HighScore", "Dans le on Create");

        super.onCreate(savedInstanceState);
        setContentView(R.layout.high_score);

        Log.d("HighScore", "Après le setContentView");

        button_close = (Button) findViewById(R.id.closing_high_score);
        input_max_pintes = (EditText) findViewById(R.id.num_max_pintes);

        button_close.setOnClickListener(button_closeListener);

    }
}
