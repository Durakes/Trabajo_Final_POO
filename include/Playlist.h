#include "Song.h"
#include <vector>

class Playlist
{
    private:
        string Name;
        int NumberSongs;
        vector<Song> Songs;
    public:
        Playlist();

        void addSong(Song song)
        {
            Songs.push_back(song);
        }
};