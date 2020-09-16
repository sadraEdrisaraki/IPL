package com.example.recyclerview;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import java.util.ArrayList;

public class MyAdapter extends RecyclerView.Adapter<MyAdapter.MyViewHolder> {

    private ArrayList<AndroidVersion> androidVersionsList;
    private OnItemClickListener listener;


    /**
     * Permet de gérer les click sur une vue de la liste
     */
    public interface OnItemClickListener {
        boolean onItemClick(int position);
    }

    /** Utilisé pour envoyer des vues au recyclerView */
    public static class MyViewHolder extends RecyclerView.ViewHolder {

        private TextView tvNameAndroidVersion;
        private TextView tvAndroidVersion;
        private ImageView ivAndroidVersion;

        public MyViewHolder(@NonNull View itemView) {
            super(itemView);
            tvAndroidVersion = itemView.findViewById(R.id.android_version);
            ivAndroidVersion = itemView.findViewById(R.id.image_version);
            tvNameAndroidVersion = itemView.findViewById(R.id.name_version);
        }

        public void setTvAndroidVersion(String androidVersion) {
            tvAndroidVersion.setText(androidVersion);
        }

        public void setIvAndroidVersion(int androidVersion) {
            ivAndroidVersion.setImageResource(androidVersion);
        }

        public void setTvNameAndroidVersion(String nameAndroidVersion) {
            tvNameAndroidVersion.setText(nameAndroidVersion);
        }
    }

    public MyAdapter (ArrayList<AndroidVersion> androidVersions){
        this.androidVersionsList = androidVersions;
    }


    public void setOnItemClickListener(OnItemClickListener listener) {
        this.listener = listener;
    }

    public void setAndroidVersionsList(ArrayList<AndroidVersion> androidVersionsList) {
        this.androidVersionsList = androidVersionsList;
    }

    /**
     * Crée la vue
     * @param parent
     * @param viewType
     * @return
     */
    @NonNull
    @Override
    public MyViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        // désérialiser le layout pour avoir un objet vue grace à inflate
        LayoutInflater layoutInflater = LayoutInflater.from(parent.getContext());

        View view = layoutInflater.inflate(R.layout.android_list_item, parent, false);

        return new MyViewHolder(view);
    }

    /**
     * Remplit la vue "courante" avec les données contenue dans le holder
     * @param holder
     * @param position
     */
    @Override
    public void onBindViewHolder(@NonNull MyViewHolder holder, int position) {
        AndroidVersion androidVersion = androidVersionsList.get(position);

        holder.setTvAndroidVersion(androidVersion.getVersion());
        holder.setIvAndroidVersion(androidVersion.getImage());
        holder.setTvNameAndroidVersion(androidVersion.getName());

        // enregistre un listener quand on appuie longtemps, sur la vue qui est dans le holder
        holder.itemView.setOnLongClickListener(v -> {
            listener.onItemClick(holder.getAdapterPosition());
            return true;
        });
    }

    @Override
    public int getItemCount() {
        return androidVersionsList.size();
    }
}
