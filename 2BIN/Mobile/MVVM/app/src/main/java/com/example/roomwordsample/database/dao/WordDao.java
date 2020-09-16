package com.example.roomwordsample.database.dao;

import androidx.lifecycle.LiveData;
import androidx.room.Dao;
import androidx.room.Delete;
import androidx.room.Insert;
import androidx.room.OnConflictStrategy;
import androidx.room.Query;

import com.example.roomwordsample.models.Word;

import java.util.List;

/**
 * Permet l'accès aux données dans la base de données
 */
@Dao
public interface WordDao {

    // allowing the insert of the same word multiple times by passing a
    // conflict resolution strategy
    @Insert(onConflict = OnConflictStrategy.IGNORE)
    void insert(Word word);

    @Query("DELETE FROM word_table")
    void deleteAll();

    @Query("SELECT * from word_table ORDER BY word ASC")
    LiveData<List<Word>> getAlphabetizedWords();

    @Query("SELECT * from word_table WHERE word LIKE :startOfWords ORDER BY word ASC")
    LiveData<List<Word>> getAllWordsFiltered(String startOfWords);

    @Delete
    void delete(Word word);
}
