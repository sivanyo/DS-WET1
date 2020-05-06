//
// Created by Mor on 30/04/2020.
//

#ifndef WET1_SONGPLAYS_H
#define WET1_SONGPLAYS_H

#include "../TreeNode/Tree.h"
#include "../Song/Song.h"

class MostPlayedListNode;
class Song;

class SongPlays {
private:
    int songId;
    int numberOfPlays = 0;
    int artistId;
    MostPlayedListNode *ptrToListNode;
    Song* ptrToSong;
public:
    SongPlays(int songId, int artistId, MostPlayedListNode *ptrToListNode);

    int getSongId() const;

    int getArtistId() const;

    int getNumberOfPlays() const;

    void setNumberOfPlays(int plays);

    void incrementNumberOfPlays();

    MostPlayedListNode *getPtrToListNode() const;

    void setPtrToListNode(MostPlayedListNode *ptr);

    Song* getPtrToSong() const;

    void setPtrToSong(Song *ptr);

    static void DeleteSongPlaysNode(TreeNode<SongPlays>* node);
};

typedef TreeNode<SongPlays> SongPlaysNode;
typedef Tree<SongPlays> SongPlaysTree;


#endif //WET1_SONGPLAYS_H
