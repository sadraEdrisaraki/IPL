package com.example.recyclerview;

import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import android.os.Bundle;

import java.util.ArrayList;

public class MainActivity extends AppCompatActivity {

    private RecyclerView recyclerView;
    private MyAdapter myAdapter;
    private ArrayList<AndroidVersion> listeAndroidsVersion;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        AndroidVersionModel androidVersionModel = new AndroidVersionModel();
        listeAndroidsVersion = androidVersionModel.getVersionsList();

        recyclerView = findViewById(R.id.recycler_view);
        LinearLayoutManager layoutManager = new LinearLayoutManager(this);
        recyclerView.setLayoutManager(layoutManager);

        myAdapter = new MyAdapter(listeAndroidsVersion);
        recyclerView.setAdapter(myAdapter);

        myAdapter.notifyDataSetChanged();

        // crée un objet héritant de l'interface et redéfinit la méthode
        myAdapter.setOnItemClickListener(new MyAdapter.OnItemClickListener() {
            @Override
            public boolean onItemClick(int position) {
                androidVersionModel.removeItem(position);
                myAdapter.setAndroidVersionsList(androidVersionModel.getVersionsList());
                myAdapter.notifyDataSetChanged();
                return true;
            }
        });

    }

}
