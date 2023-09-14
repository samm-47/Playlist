#include <cstring>
#include <iostream>

using namespace std;
class PlaylistNode {

private:
  string uniqueID;
  string songName;
  string artistName;
  int songLength;
  PlaylistNode *nextNodePtr;

public:
  PlaylistNode() {
    uniqueID = "none";
    songName = "none";
    artistName = "none";
    songLength = 0;
    nextNodePtr = nullptr;
  }
  PlaylistNode(string id, string song, string artist, int length,
               PlaylistNode *nextPtr) {
    uniqueID = id;
    songName = song;
    artistName = artist;
    songLength = length;
    nextNodePtr = nextPtr;
  }

public:
  // PlaylistNode();
  PlaylistNode(string id, string songname, string artist, int length);
  void InsertAfter(PlaylistNode *ptr);
  void SetNext(PlaylistNode *ptr);
  string GetID();
  string GetSongName();
  string GetArtistName();
  int GetSongLength();
  PlaylistNode *GetNext();
  void PrintPlaylistNode();
};
class Playlist {
public:
  Playlist();
  void AddSong(string id, string songname, string artistname, int length);
  bool RemoveSong(string id);
  void PrintList();
  bool ChangePosition(int oldPos, int newPos);
  void SongsByArtist(string artist);
  int TotalTime();
private:
  PlaylistNode *head;
  PlaylistNode *tail;


};