package be.ipl.compteurdepintes;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

public class Panic extends AppCompatActivity {


    private Button sendSMS;


    private View.OnClickListener sendSMSListener = new View.OnClickListener() {
        @Override
        public void onClick(View v) {

        }
    };

    @Override
    public void onCreate(@Nullable Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        setContentView(R.layout.panic);

        Log.d("Panic", "Dans l'écran Panic");

        sendSMS = (Button) findViewById(R.id.sendSMS);

        sendSMS.setOnClickListener(sendSMSListener);
    }
}
