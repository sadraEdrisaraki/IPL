package com.example.roomwordsample;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;
import androidx.lifecycle.Observer;
import androidx.lifecycle.ViewModelProvider;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.EditText;
import android.widget.Toast;

import com.example.roomwordsample.models.Word;
import com.google.android.material.floatingactionbutton.FloatingActionButton;

import java.util.List;


public class MainActivity extends AppCompatActivity {

    private final Context context = this;
    private WordViewModel mWordViewModel;
    public static final int NEW_WORD_ACTIVITY_REQUEST_CODE = 1;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.activity_main);

        RecyclerView recyclerView = findViewById(R.id.recyclerview);

        final WordListAdapter adapter = new WordListAdapter(this);

        recyclerView.setAdapter(adapter);
        recyclerView.setLayoutManager(new LinearLayoutManager(this));

        // Le viewModel persiste même quand l'activité est détruite.
        mWordViewModel = new ViewModelProvider(this).get(WordViewModel.class);

        // Créer le listener et redéfinit la méthode OnItemClick; dans ce cas quand on longclick
        // sur la mini vue une boite de dialogue apparait
        adapter.setOnItemClickListener(new WordListAdapter.OnItemClickListener() {
            @Override
            public boolean onItemClick(int positionRecyclerViewAndArray) {
                AlertDialog.Builder builder = new AlertDialog.Builder(context);
                builder.setTitle("Confirm");
                builder.setMessage("Are you sure?");
                builder.setPositiveButton("YES", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        // Récupère le mot à la position clicker
                        Word word = mWordViewModel.getAllWords().getValue().get(positionRecyclerViewAndArray);
                        mWordViewModel.delete(word);
                        dialog.dismiss();
                    }
                });

                builder.setNegativeButton("NO", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        // Do nothing
                        dialog.dismiss();
                    }
                });
                //affichage
                AlertDialog alertDialog = builder.create();
                alertDialog.show();

                return true;
            }
        });

        // Rajoute un observer sur le LIVEDATA retourné par @getAlphabetizeWords().
        // La méthode onChanged() est appelé lorsque les données observées changent et que l'activité
        // est au au premier plan.
        mWordViewModel.getAllWords().observe(this, new Observer<List<Word>>() {

            @Override
            public void onChanged(@NonNull List<Word> words) {
                // Update the cached copy of the words in the adapter.
                Log.d("MainActivity", "Les données ont changé : Mise à jour de la liste sans filtre");
                adapter.setWords(words);
            }
        });

        FloatingActionButton fab = findViewById(R.id.fab);
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, NewWordActivity.class);
                startActivityForResult(intent, NEW_WORD_ACTIVITY_REQUEST_CODE);
            }
        });

        // Button filtre
        FloatingActionButton fab_filter = findViewById(R.id.filter);
        fab_filter.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View v) {

                LayoutInflater layoutInflater = LayoutInflater.from(context);
                View promptsView = layoutInflater.inflate(R.layout.prompts,null);

                AlertDialog.Builder alertDialogBuilder = new AlertDialog.Builder(context);

                //set prompts.xml to alertDialgoBuilder
                alertDialogBuilder.setView(promptsView);

                final EditText userInput = promptsView.findViewById(R.id.editTextDialogUserInput);

                // set dialog message : listener on "sort" and listener on "cancel"
                alertDialogBuilder
                        .setCancelable(false)
                        .setPositiveButton("Sort", new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialog, int which) {
                                String filter = userInput.getText().toString();

                                // Observer sur le LiveData retourner par la méhode @getAllWordsFiltered(filter)
                                mWordViewModel.getAllWordsFiltered(filter).observe(MainActivity.this, new Observer<List<Word>>() {
                                    // Méthode appelé si le liveData retourner par la méthode @getAllWordsFiltered(filter) à changer
                                    // Il peut changer quand on rajoute un nouveau de la lettre filtrer.
                                    @Override
                                    public void onChanged(List<Word> words) {
                                        Log.d("MainActivity", "Les données ont changé : Mise à jour de la liste avec filtre");
                                        //Update the cached data
                                        adapter.setWords(words);
                                    }
                                });
                            }
                        })
                        .setNegativeButton("Cancel", new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialog, int which) {
                                dialog.cancel();
                            }
                        });
                // After set : create alert dialog
                AlertDialog alertDialog = alertDialogBuilder.create();

                //show it
                alertDialog.show();
            }
        });

    }

    public void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        if (requestCode == NEW_WORD_ACTIVITY_REQUEST_CODE && resultCode == RESULT_OK) {
            Word word = new Word(data.getStringExtra(NewWordActivity.EXTRA_REPLY));
            mWordViewModel.insert(word);
        } else {
            Toast.makeText(
                    getApplicationContext(),
                    R.string.empty_not_saved,
                    Toast.LENGTH_LONG).show();
        }
    }
}
