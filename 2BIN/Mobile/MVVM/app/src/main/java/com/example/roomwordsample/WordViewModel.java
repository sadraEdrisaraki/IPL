package com.example.roomwordsample;

import android.app.Application;

import androidx.lifecycle.AndroidViewModel;
import androidx.lifecycle.LiveData;

import com.example.roomwordsample.models.Word;

import java.util.List;

/**
 * Son rôle est de fournir des données à l'interface.
 * Communication entre l'UI et le repository.
 */
public class WordViewModel extends AndroidViewModel {

    private WordRepository mRepository;
    private LiveData<List<Word>> mAllWords;

    public WordViewModel (Application application) {
        super(application);
        mRepository = new WordRepository(application);
        mAllWords = mRepository.getAllWords();
    }

    LiveData<List<Word>> getAllWords() { return mAllWords; }

    LiveData<List<Word>> getAllWordsFiltered(String startOfWords) {
        return mRepository.getAllWordsFiltered(startOfWords);
    }

    public void insert(Word word) { mRepository.insert(word); }

    public void delete(Word word) { mRepository.delete(word);}
}
