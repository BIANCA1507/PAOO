#ifndef SONG_HPP
#define SONG_HPP

#include <iostream>
#include <cstring>

class Song {
private:
    char* title;      
    char* artist;     
    int duration;     
    
    void cleanup();
    
public:
    Song(const char* t, const char* a, int d);
    
    Song(const Song& other);
    
    Song(Song&& other) noexcept;
    
    ~Song();
    
    const char* getTitle() const;
    const char* getArtist() const;
    int getDuration() const;
    void display() const;
};

#endif 