#include "PlaylistNode.h"
#include "string"
#include <cstring>
#include <iostream>
using namespace std;
int removedSongLength = 0;

PlaylistNode::PlaylistNode(string id, string songName, string artist,
                           int length) {
  uniqueID = id;
  this->songName = songName;
  this->artistName = artist;
  songLength = length;
  nextNodePtr = nullptr;
}

void PlaylistNode::InsertAfter(PlaylistNode *node) {
  this->SetNext(node->GetNext());
  node->SetNext(this);
}

//Acessor (s)
string PlaylistNode::GetID() { return uniqueID; }

string PlaylistNode::GetSongName() { return songName; }

string PlaylistNode::GetArtistName() { return artistName; }

int PlaylistNode::GetSongLength() { return songLength; }

PlaylistNode *PlaylistNode::GetNext() { return nextNodePtr; }
//Mutator
void PlaylistNode::SetNext(PlaylistNode *node) { nextNodePtr = node; }
//Outputs uniqueID, songname, artistName, and songLength
void PlaylistNode::PrintPlaylistNode() {
  cout << "Unique ID: " << uniqueID << endl;
  cout << "Song Name: " << songName << endl;
  cout << "Artist Name: " << artistName << endl;
  cout << "Song Length (in seconds): " << songLength << endl;
}

Playlist::Playlist() { head = tail = 0; }
//Adds song to the end
void Playlist::AddSong(string id, string songName, string artist, int length) {
  PlaylistNode *n = new PlaylistNode(id, songName, artist, length);
  if (head == 0)
    head = tail = n;
  else {
    n->InsertAfter(tail);
    tail = n;
  }
}
//removes any song based on ID
bool Playlist::RemoveSong(string id) {
  if (head == NULL) {
    cout << "Playlist is empty." << endl;
    return false;
  }

  PlaylistNode *curr = head;
  PlaylistNode *prev = NULL;
  while (curr != NULL) {
    if (curr->GetID() == id) {
      break;
    }
    prev = curr;
    curr = curr->GetNext();
  }

  if (curr == NULL) {
    cout << curr->GetSongName() << " is not found" << endl;
    return false;
  } else {
    if (prev != NULL)
      prev->SetNext(curr->GetNext());
    else
      head = curr->GetNext();

    if (tail == curr)
      tail = prev;
    cout << "\"" << curr->GetSongName() << "\" removed" << endl;
    delete curr;
    return true;
  }
}
typedef void (*InsertAfterFuncPtr)(PlaylistNode*, PlaylistNode*);

void InsertAfterDefault(PlaylistNode* nodeToInsert, PlaylistNode* prevNode) {
    prevNode->InsertAfter(nodeToInsert);
}
//changes the position to the new desired position
bool Playlist::ChangePosition(int pos1, int newPos) {
  if (head == NULL) {
    cout << "Playlist is empty." << endl;
    return false;
  }

  PlaylistNode *prev = NULL;
  PlaylistNode *newNode = head;

  int pos;
  if (head == NULL || head == tail)
    return false;

  for (pos = 1; newNode != NULL && pos < pos1; pos++) {
    prev = newNode;
    newNode = newNode->GetNext();
  }
  if (newNode != NULL) {
    string currentSong = newNode->GetSongName();

    if (prev == NULL)
      head = newNode->GetNext();
    else {
      prev->SetNext(newNode->GetNext());
    }

    if (newNode == tail)
      tail = prev;

    PlaylistNode *current = newNode;
    prev = NULL;
    newNode = head;

    for (pos = 1; newNode != NULL && pos < newPos; pos++) {
      prev = newNode;
      newNode = newNode->GetNext();
    }

    if (prev == NULL) {
      current->SetNext(head);
      head = current;
    } else
      current->InsertAfter(prev);

    if (newNode == NULL)
      tail = current;

    cout << currentSong << " moved to position " << newPos << endl;
    return true;

  } else {
    cout << "Song's current position is invalid" << endl;
    return false;
  }
}
//Outputs based on artist name
void Playlist::SongsByArtist(string artist) {
  //if it is empty
  if (head == nullptr) {
    cout << "Playlist is empty." << endl;
  } else {
    PlaylistNode *currentNode = head;
    int pos = 1;
    bool found = false;

    while (currentNode != nullptr) {
      if (currentNode->GetArtistName() == artist) {
        cout << pos << "." << endl;
        currentNode->PrintPlaylistNode();
        found = true;
      }
      currentNode = currentNode->GetNext();
      pos++;
    }

    if (!found) {
      cout << "No songs found by artist " << artist << "." << endl;
    }
  }
}

int Playlist::TotalTime() {
  int total = 0;
  PlaylistNode *node = head;

  while (node != NULL) {
   
    total += node->GetSongLength();
    node = node->GetNext();
  }

  return total;
}

void Playlist::PrintList() {
  if (head == nullptr) {
    cout << "Playlist is empty." << endl;
  } else {
    PlaylistNode *node = head;
    int i = 1;
    while (node != nullptr) {
      cout << endl << i << "." << endl;
      node->PrintPlaylistNode();
      node = node->GetNext();
      i++;
    }
  }
}
