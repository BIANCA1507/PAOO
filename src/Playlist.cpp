#include "Playlist.hpp"
#include <iostream>
#include <cstring>
#include <iomanip>   

using namespace std;

// Constructor Normal
Playlist::Playlist(const char* n) 
    : name(nullptr),
      songs(nullptr),
      capacity(4),
      size(0)
{
    cout << "\nPlaylist Constructor: Creating " << n << endl;
    
    name = new char[strlen(n) + 1];
    strcpy(name, n);
    
    songs = new Song*[capacity];
    
    for (int i = 0; i < capacity; i++) {
        songs[i] = nullptr;
    }
}

// Copy Constructor - DEEP COPY
Playlist::Playlist(const Playlist& other) 
    : name(nullptr), 
      songs(nullptr), 
      capacity(other.capacity), 
      size(other.size)
{
    cout << "\nPlaylist Copy Constructor: Copying " << other.name << endl;
    cout << "Copying " << other.size << " songs..." << endl;
    
    if (other.name) {
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
    }
    
    songs = new Song*[capacity];

    for (int i = 0; i < size; i++) {
        songs[i] = new Song(*other.songs[i]);
    }
    
    for (int i = size; i < capacity; i++) {
        songs[i] = nullptr;
    }
    
    cout << "Deep copy completed: " << size << " songs copied" << endl;
}

// Move Constructor
Playlist::Playlist(Playlist&& other) noexcept 
    : name(other.name),
      songs(other.songs),
      capacity(other.capacity),
      size(other.size)
{
    cout << "\n[Move Constructor] Moving playlist: " 
         << (other.name ? other.name : "null") << endl;
    cout << "Transferring " << size << " songs (no deep copy)" << endl;

    // Invalidate source
    other.name = nullptr;
    other.songs = nullptr;
    other.capacity = 0;
    other.size = 0;
}


Playlist::~Playlist() {
    cout << "\nPlaylist Destructor: Destroying " 
         << (name ? name : "null") << endl;
    
    cleanup();
}

// Adauga melodie prin COPY
void Playlist::addSong(const Song& song) {
    cout << "Adding song: " << song.getTitle() << endl;
    
    if (size >= capacity) {
        resize();
    }
    
    songs[size] = new Song(song);
    size++;
}

// Sterge melodie
void Playlist::removeSong(int index) {
    if (index < 0 || index >= size) {
        cout << "Invalid index!" << endl;
        return;
    }
    
    cout << "Removing: " << songs[index]->getTitle() << endl;
    
    delete songs[index];
    
    for (int i = index; i < size - 1; i++) {
        songs[i] = songs[i + 1];
    }
    
    songs[size - 1] = nullptr;
    size--;
}

// Afiseaza playlist-ul
void Playlist::displayPlaylist() const {
    if (songs == nullptr || size == 0) {
        cout << "  (Empty playlist)" << endl;
        return;
    }

    cout << "Playlist: " << (name ? name : "(unnamed)") << "\n\n";
    for (int i = 0; i < size; ++i) {
        cout << i + 1 << ".  ";
        songs[i]->display();
    }

    int totalDuration = 0;
    for (int i = 0; i < size; ++i) {
        totalDuration += songs[i]->getDuration();
    }

    int minutes = totalDuration / 60;
    int seconds = totalDuration % 60;
    cout << "Total: " << size << " songs, "
         << minutes << ":" << setw(2) << setfill('0') << seconds << "\n";
}


// Calculeaza durata totala
int Playlist::getTotalDuration() const {
    int total = 0;
    for (int i = 0; i < size; i++) {
        total += songs[i]->getDuration();
    }
    return total;
}

int Playlist::getSize() const {
    return size;
}

const char* Playlist::getName() const {
    return name;
}

bool Playlist::isEmpty() const {
    return size == 0;
}

// Redimensionare automata (helper privat)
void Playlist::resize() {
    cout << "Resizing: capacity " << capacity;
    
    int newCapacity = capacity * 2;
    Song** newSongs = new Song*[newCapacity];
    
    for (int i = 0; i < size; i++) {
        newSongs[i] = songs[i];
    }
    
    for (int i = size; i < newCapacity; i++) {
        newSongs[i] = nullptr;
    }
    
    delete[] songs;
    
    songs = newSongs;
    capacity = newCapacity;
    
    cout << " -> " << capacity << endl;
}

// Cleanup helper
void Playlist::cleanup() {
    if (songs) {
        for (int i = 0; i < size; i++) {
            delete songs[i];
        }
        delete[] songs;
    }
    
    delete[] name;
    
    songs = nullptr;
    name = nullptr;
    size = 0;
    capacity = 0;
}