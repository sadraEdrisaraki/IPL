package com.example.roomwordsample;

import android.app.Application;

import androidx.lifecycle.LiveData;

import com.example.roomwordsample.database.WordRoomDatabase;
import com.example.roomwordsample.database.dao.WordDao;
import com.example.roomwordsample.models.Word;

import java.util.List;

/**
 * Rôle de médiateur entre le ViewModel et les différentes sources de données
 * (ici : DAO est la source de données). Là ou le viewModel vient récupéré les données.
 * Le viewModel ne sait pas d'où les données proviennent (DAO ou API)
 */
public class WordRepository {

    private WordDao mWordDao;
    private LiveData<List<Word>> mAllWords;

    // Note that in order to unit test the WordRepository, you have to remove the Application
    // dependency. This adds complexity and much more code, and this sample is not about testing.
    // See the BasicSample in the android-architecture-components repository at
    // https://github.com/googlesamples
    WordRepository(Application application) {
        WordRoomDatabase db = WordRoomDatabase.getDatabase(application);
        mWordDao = db.wordDao();
        mAllWords = mWordDao.getAlphabetizedWords();
    }

    // Room executes all queries on a separate thread.
    // Observed LiveData will notify the observer when the data has changed.
    LiveData<List<Word>> getAllWords() {
        return mAllWords;
    }

    /**
     * Retourne un LiveData d'une liste de "word" filtré selon le mot passé en paramètre
     * @param startOfWords
     * @return
     */
    LiveData<List<Word>> getAllWordsFiltered(String startOfWords) {
        return mWordDao.getAllWordsFiltered(startOfWords + "%");
    }

    // You must call this on a non-UI thread or your app will throw an exception. Room ensures
    // that you're not doing any long running operations on the main thread, blocking the UI.
    void insert(Word word) {
        WordRoomDatabase.databaseWriteExecutor.execute(() -> {
            mWordDao.insert(word);
        });
    }

    void delete(Word word) {
        WordRoomDatabase.databaseWriteExecutor.execute(() -> {
            mWordDao.delete(word);
        });
    }
}
