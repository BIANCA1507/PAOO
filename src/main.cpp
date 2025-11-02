#include "Playlist.hpp"
#include <iostream>
#include <limits>

using namespace std;

// Demonstrates COPY CONSTRUCTOR
void demonstrateCopyConstructor() {
    cout << "\n--- Copy Constructor Demo ---\n";

    Playlist original("My Favorites");
    original.addSong(Song("Tit for tat", "Tate Mcrae", 185));
    original.addSong(Song("Sympathy is a knife", "Charli XCX", 159));

    cout << "Duplicating playlist...\n";
    Playlist copy = original;  // copy constructor

    copy.addSong(Song("Crazy", "Lesserafim", 185));

    cout << "\nOriginal playlist:\n";
    original.displayPlaylist();

    cout << "\nCopied playlist:\n";
    copy.displayPlaylist();
}


// Demonstrates MOVE CONSTRUCTOR
void demonstrateMoveConstructor() {
    cout << "\n--- Move Constructor Demo ---\n";

    Playlist source("Summer Vibes\n");
    source.addSong(Song("Espresso", "Sabrina Carpenter", 183));
    source.addSong(Song("Go", "Cortis", 167));
    source.addSong(Song("Sports Car", "Tate McRae", 201));

    cout << "\nOriginal playlist before transfer:\n";
    source.displayPlaylist();

    cout << "\nTransferring ownership to another playlist...\n";

    Playlist destination = std::move(source);

    cout << "\nDestination playlist after move:\n";
    destination.displayPlaylist();

    cout << "\nSource playlist after move (should be empty or null):\n";
    source.displayPlaylist();

    cout << "\nMove constructor was called — ownership transferred safely.\n";
}




void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void showMenu() {
    cout << "\n========================================" << endl;
    cout << "      PLAYLIST MANAGER - MENU" << endl;
    cout << "========================================" << endl;
    cout << "  1. Create new playlist" << endl;
    cout << "  2. Add song to playlist" << endl;
    cout << "  3. Display playlist" << endl;
    cout << "  4. Duplicate playlist (copy)" << endl;
    cout << "  5. Remove song" << endl;
    cout << "  6. Show total duration" << endl;
    cout << "  7. Run demonstrations" << endl;
    cout << "  0. Exit" << endl;
    cout << "========================================" << endl;
    cout << "Choose option: ";
}


int main() {

    Playlist* currentPlaylist = nullptr;
    Playlist* backupPlaylist = nullptr;
    
    bool running = true;
    int choice;
    
    while (running) {
        showMenu();
        
        if (!(cin >> choice)) {
            clearInputBuffer();
            cout << "Invalid input! Please enter a number." << endl;
            continue;
        }
        clearInputBuffer();
        
        switch (choice) {
            case 1: {
                cout << "\nEnter playlist name: ";
                char name[100];
                cin.getline(name, 100);
                
                if (currentPlaylist != nullptr) {
                    cout << "Deleting old playlist..." << endl;
                    delete currentPlaylist;
                }
                
                currentPlaylist = new Playlist(name);
                cout << "Playlist created successfully!" << endl;
                break;
            }
            
            case 2: {
                if (currentPlaylist == nullptr) {
                    cout << "Please create a playlist first!" << endl;
                    break;
                }
                
                cout << "\nEnter song title: ";
                char title[100];
                cin.getline(title, 100);
                
                cout << "Enter artist: ";
                char artist[100];
                cin.getline(artist, 100);
                
                cout << "Enter duration (seconds): ";
                int duration;
                if (!(cin >> duration) || duration <= 0) {
                    clearInputBuffer();
                    cout << "Invalid duration!" << endl;
                    break;
                }
                clearInputBuffer();
                
                Song newSong(title, artist, duration);
                currentPlaylist->addSong(newSong);
                
                cout << "Song added successfully!" << endl;
                break;
            }
            
            case 3: {
                if (currentPlaylist == nullptr) {
                    cout << "No playlist to display!" << endl;
                    break;
                }
                
                currentPlaylist->displayPlaylist();
                
                if (backupPlaylist != nullptr) {
                    cout << "\nBackup playlist:" << endl;
                    backupPlaylist->displayPlaylist();
                }
                break;
            }
            
            case 4: {
                if (currentPlaylist == nullptr) {
                    cout << "No playlist to duplicate!" << endl;
                    break;
                }
                
                cout << "\nCreating backup using copy constructor..." << endl;
                
                if (backupPlaylist != nullptr) {
                    delete backupPlaylist;
                }
                
                backupPlaylist = new Playlist(*currentPlaylist);
                
                cout << "Playlist duplicated successfully!" << endl;
                cout << "Both playlists are independent (deep copy)" << endl;
                break;
            }
            
            case 5: {
                if (currentPlaylist == nullptr || currentPlaylist->isEmpty()) {
                    cout << "No songs to remove!" << endl;
                    break;
                }
                
                currentPlaylist->displayPlaylist();
                cout << "\nEnter song number to remove (1-" << currentPlaylist->getSize() << "): ";
                
                int index;
                if (!(cin >> index) || index < 1 || index > currentPlaylist->getSize()) {
                    clearInputBuffer();
                    cout << "Invalid song number!" << endl;
                    break;
                }
                clearInputBuffer();
                
                currentPlaylist->removeSong(index - 1);
                cout << "Song removed!" << endl;
                break;
            }
            
            case 6: {
                if (currentPlaylist == nullptr) {
                    cout << "No playlist!" << endl;
                    break;
                }
                
                int total = currentPlaylist->getTotalDuration();
                int hours = total / 3600;
                int minutes = (total % 3600) / 60;
                int seconds = total % 60;
                
                cout << "\n--- Playlist Statistics ---" << endl;
                cout << "Playlist: " << currentPlaylist->getName() << endl;
                cout << "Total songs: " << currentPlaylist->getSize() << endl;
                cout << "Duration: ";
                if (hours > 0) {
                    cout << hours << "h " << minutes << "m " << seconds << "s" << endl;
                } else {
                    cout << minutes << "m " << seconds << "s" << endl;
                }
                break;
            }
            
            case 7: {
                cout << "\n========================================" << endl;
                cout << "       RUNNING DEMONSTRATIONS" << endl;
                cout << "========================================" << endl;
                
                demonstrateCopyConstructor();
                
                cout << "\n[Press Enter to continue to Move Constructor demo...]";
                cin.get();
                
                demonstrateMoveConstructor();
                
                cout << "\n[Press Enter to return to menu...]";
                cin.get();
                break;
            }
            
            case 0: {
                running = false;
                break;
            }
            
            default: {
                cout << "Invalid option! Please choose 0-7." << endl;
                break;
            }
        }
    }
        
    if (currentPlaylist != nullptr) {
        delete currentPlaylist;
        currentPlaylist = nullptr;
    }
    
    if (backupPlaylist != nullptr) {
        delete backupPlaylist;
        backupPlaylist = nullptr;
    }
        return 0;
}