#ifndef PLAYLIST_HPP
#define PLAYLIST_HPP

#include "Song.hpp"

class Playlist {
private:
    char* name;           
    Song** songs;         
    int capacity;         
    int size;             
    
    void resize();
    void cleanup();
    
public:
    Playlist(const char* n);
    
    Playlist(const Playlist& other);
    
    Playlist(Playlist&& other) noexcept;
    
    ~Playlist();
    
    void addSong(const Song& song);           
    void removeSong(int index);
    void displayPlaylist() const;
    int getTotalDuration() const;             
    int getSize() const;
    const char* getName() const;
    bool isEmpty() const;
};

#endif 