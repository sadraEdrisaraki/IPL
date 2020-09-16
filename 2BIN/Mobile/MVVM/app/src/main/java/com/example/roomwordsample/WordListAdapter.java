package com.example.roomwordsample;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import androidx.recyclerview.widget.RecyclerView;

import com.example.roomwordsample.models.Word;

import java.util.List;

public class WordListAdapter extends RecyclerView.Adapter<WordListAdapter.WordViewHolder> {

    // Gestion des cliques pour permettre de notifié l'activité qu'un des éléments a été cliquer
    public interface OnItemClickListener {
        boolean onItemClick(int positionRecyclerViewAndArray);
    }

    /**
     * Représente une vue (ligne) dans la recyclerView. Le viewHolder comporte les éléments du fichier XML.
     * Permet donc de modéliser en objet Java la vue XML.
     */
    class WordViewHolder extends RecyclerView.ViewHolder {
        private final TextView wordItemView;

        private WordViewHolder(View itemView) {
            super(itemView);
            wordItemView = itemView.findViewById(R.id.textView);
        }
    }


    private final LayoutInflater mInflater;
    private List<Word> mWords; // Cached copy of words
    private OnItemClickListener onItemClickListener;


    WordListAdapter(Context context) { mInflater = LayoutInflater.from(context); }

    /**
     * Méthode qui nous permet de créer un ViewHolder à partir du layout XML représentant chaque ligne
     * de la recyclerView. Cette méthode sera appelé pour les premières lignes visibles car les autres vues seront
     * recycler.
     * @param parent
     * @param viewType
     * @return
     */
    @Override
    public WordViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        View itemView = mInflater.inflate(R.layout.recyclerview_item, parent, false);
        return new WordViewHolder(itemView);
    }


    /**
     * Cette méthode est appelé pour chacune des lignes visibles affichées dans la recyclerView
     * Elle remplit la ViewHolder avec les données à la position reçu.
     * Si une vue est recycler elle sera remplit ici aussi.
     * @param holder
     * @param position
     */
    @Override
    public void onBindViewHolder(WordViewHolder holder, int position) {
        if (mWords != null) {
            Word current = mWords.get(position);
            holder.wordItemView.setText(current.getWord());
        } else {
            // Covers the case of data not being ready yet.
            holder.wordItemView.setText("No Word");
        }

        // associe un listener à la vue, une fois cliquer dessus on fait appel à la methode on itemClik
        holder.itemView.setOnLongClickListener(new View.OnLongClickListener() {
            @Override
            public boolean onLongClick(View v) {
                return onItemClickListener.onItemClick(position);
            }
        });
    }

    void setWords(List<Word> words){
        mWords = words;
        notifyDataSetChanged();
    }

    // getItemCount() is called many times, and when it is first called,
    // mWords has not been updated (means initially, it's null, and we can't return null).
    @Override
    public int getItemCount() {
        if (mWords != null)
            return mWords.size();
        else return 0;
    }

    /**
     * Permet de s'enregistrer sur l'adapter
     */
    public void setOnItemClickListener(OnItemClickListener listener) {
        this.onItemClickListener = listener;
    }
}
