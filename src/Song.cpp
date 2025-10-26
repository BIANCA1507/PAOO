#include "Song.hpp"

// Constructor Normal
Song::Song(const char* t, const char* a, int d) 
    : title(nullptr),    
      artist(nullptr), 
      duration(d)        
{
    std::cout << "[Constructor] Creating song: " << t << " by " << a << std::endl;
    
    title = new char[strlen(t) + 1];
    strcpy(title, t);
    
    artist = new char[strlen(a) + 1];
    strcpy(artist, a);
}

// Copy Constructor
Song::Song(const Song& other) 
    : title(nullptr), 
      artist(nullptr), 
      duration(other.duration)  
{
    std::cout << "[Copy] " << other.title << std::endl;
    
    if (other.title) {
        title = new char[strlen(other.title) + 1];
        strcpy(title, other.title);
    }
    
    if (other.artist) {
        artist = new char[strlen(other.artist) + 1];
        strcpy(artist, other.artist);
    }
    
    std::cout << "[Copy Constructor] Deep copy completed successfully!" << std::endl;
}

// Move Constructor
Song::Song(Song&& other) noexcept 
    : title(other.title),      
      artist(other.artist),    
      duration(other.duration)
{
    std::cout << "[Move Constructor] Moving song: " << (other.title ? other.title : "null") << std::endl;
    other.title = nullptr;
    other.artist = nullptr;
    other.duration = 0;
}

// Destructor
Song::~Song() {
    std::cout << "[Destroy] " << (title ? title : "null") << std::endl;

    delete[] title;
    delete[] artist;
}

// Getters
const char* Song::getTitle() const {
    return title;
}

const char* Song::getArtist() const {
    return artist;
}

int Song::getDuration() const {
    return duration;
}

void Song::display() const {
    int minutes = duration / 60;
    int seconds = duration % 60;
    std::cout << " \"" << title << "\" - " << artist 
              << " [" << minutes << ":" << (seconds < 10 ? "0" : "") << seconds << "]" 
              << std::endl;
}
