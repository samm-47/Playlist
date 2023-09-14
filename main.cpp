#include "PlaylistNode.h"
#include "string"
#include <climits>
#include <iostream>
using namespace std;
string playList;
int length;
string ID, name, song;
void PrintMenu(const string playlistTitle) {
  /* Type your code here */
  cout << playlistTitle << " PLAYLIST MENU " << endl;
  cout << "a - Add song " << endl;
  cout << "d - Remove song" << endl;
  cout << "c - Change position of song" << endl;
  cout << "s - Output songs by specific artist" << endl;
  cout << "t - Output total time of playlist (in seconds)" << endl;
  cout << "o - Output full playlist" << endl;
  cout << "q - Quit" << endl;
}

void ExecuteMenu(char option, string playlistTitle, PlaylistNode *headNode) {

  Playlist list;
  bool playlistPrinted = false;
  // if option is q, then it will end
  while (option != 'q' || option == 'Q') {
    // option o OR option c
    if ((option == 'o' || option == 'O') || (option == 'c' || option == 'C')) {
      if ((option == 'o' || option == 'O')) {
        PlaylistNode *currentNode = headNode;
        int position = 1;

        if (currentNode != nullptr) {

          list.PrintList();
        }
        if (headNode == nullptr) {
          cout << "Playlist is empty." << endl;
        }
        playlistPrinted = true;
      }
      if ((option == 'c' || option == 'C')) {
        int newPosition, oldPosition;
        cout << "CHANGE POSITION OF SONG" << endl;
        cout << "Enter song's current position: ";
        cin >> oldPosition;
        cout << "Enter new position for song: ";
        cin >> newPosition;
        list.ChangePosition(oldPosition, newPosition);
      }
      // outputs menu after action is completed
      PrintMenu(playList);
      cin >> option;

    }
    // option a OR option t
    else if ((option == 'a' || option == 'A') ||
             ((option == 't' || option == 'T'))) {
      if ((option == 'a' || option == 'A')) {
        int length;
        string ID, name, song;
        // outputs and inputs
        cout << "ADD SONG" << endl;

        cout << "Enter song's unique ID: ";
        cin >> ID;

        cout << "Enter songs's name: ";
        // ignores the space
        cin.ignore();
        getline(cin, song);

        cout << "Enter artist's name: ";

        getline(cin, name);

        cout << "Enter song's length (in seconds): ";
        cin >> length;
        //Adds song to playlist
        list.AddSong(ID, song, name, length);

        PlaylistNode *newNode = new PlaylistNode(ID, song, name, length);
        if (headNode == nullptr) {
          headNode = newNode;
        } else {
          PlaylistNode *currentNode = headNode;
          while (currentNode->GetNext() != nullptr) {
            currentNode = currentNode->GetNext();
          }
          currentNode->SetNext(newNode);
        }
      }
      //Total time of songs on playlist
      if ((option == 't' || option == 'T')) {
        cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl;
        cout << "Total time: " << list.TotalTime() << " seconds" << endl;
        cout << endl;
      }

      PrintMenu(playList);
      cin >> option;
    }
    // option d OR option s
    else if ((option == 'd' || option == 'D') ||
             (option == 's' || option == 'S')) {
      if ((option == 'd' || option == 'D')) {
        int print = 0;
        PlaylistNode *currentNode = headNode;
        if (headNode == nullptr) {
          cout << "Playlist is empty. " << endl;
        } else {
          if (print == 0) {
            PlaylistNode *currentNode = headNode;
            cout << "REMOVE SONG" << endl;
            cout << "Enter song's unique ID: ";
            cin >> ID;

            while (currentNode != nullptr) {
              if (currentNode->GetID() == ID) {
                cout << "\"" << currentNode->GetSongName() << "\""
                     << " removed." << endl;
                print++;
                break;
              }
              currentNode = currentNode->GetNext();
            }
          }
          //If inputted ID is invaild
          if (currentNode == nullptr) {
            cout << "Song with ID " << ID << " not found." << endl;
          }
          if (print == 1) {
            playlistPrinted = false;
            PrintMenu(playList);
            cin >> option;
            list.RemoveSong(ID);
          }
        }
      }
      if (option == 's' || option == 'S') {
        if (headNode == nullptr) {
          cout << "Empty Playlist" << endl;
        } else {
          cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl;
          cout << "Enter artist's name: ";
          cin.ignore();
          getline(cin, name);

          bool found = false;
          PlaylistNode *currentNode = headNode;

          while (currentNode != nullptr) {
            if (currentNode->GetArtistName() == name) {
              list.SongsByArtist(name);
              break; // Exit the loop after finding the first match
            }
            currentNode = currentNode->GetNext();
          }

          if (found) {
            list.SongsByArtist(name);
          }
        }

        PrintMenu(playList);
        cin >> option;
      }
    }
  }
}

int main() {
  char option;
  PlaylistNode *headNode = nullptr;

  cout << "Enter playlist's title: ";

  getline(cin, playList);
  PrintMenu(playList);
  cin >> option;

  ExecuteMenu(option, playList, headNode);

  return 0;
}
