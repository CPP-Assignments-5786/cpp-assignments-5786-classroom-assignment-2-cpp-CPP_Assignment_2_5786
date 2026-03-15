/**
 * @file main.cpp
 * @brief Demo for Music Library Management System
 */

#include <iostream>
#include "Song.hpp"
#include "Playlist.hpp"
#include "MusicLibrary.hpp"

using namespace music;

int main() {
    // Create some songs
    Song s1("Bohemian Rhapsody", "Queen", 355);
    Song s2("Stairway to Heaven", "Led Zeppelin", 482);
    Song s3("Hotel California", "Eagles", 391);

    std::cout << "Songs:\n";
    std::cout << s1.getTitle() << " by " << s1.getArtist() << " [" << s1.getFormattedDuration() << "]\n";
    std::cout << s2.getTitle() << " by " << s2.getArtist() << " [" << s2.getFormattedDuration() << "]\n";
    std::cout << s3.getTitle() << " by " << s3.getArtist() << " [" << s3.getFormattedDuration() << "]\n";
    // Expected:
    // Songs:
    // Bohemian Rhapsody by Queen [5:55]
    // Stairway to Heaven by Led Zeppelin [8:02]
    // Hotel California by Eagles [6:31]

    // Test copy constructor
    Song s1Copy(s1);
    std::cout << "\nCopy: " << s1Copy.getTitle() << " by " << s1Copy.getArtist() << "\n";
    // Expected: Copy: Bohemian Rhapsody by Queen

    // Test setters
    s1Copy.setTitle("Bohemian Rhapsody (Live)");
    std::cout << "After setTitle: " << s1Copy.getTitle() << "\n";
    // Expected: After setTitle: Bohemian Rhapsody (Live)

    // Create playlist and add songs
    Playlist rock("Rock Classics", 2);
    rock.addSong(s1);
    rock.addSong(s2);
    rock.addSong(s3);  // triggers resize

    std::cout << "\nPlaylist: " << rock.getName() << " (" << rock.getCount() << " songs)\n";
    std::cout << "Total duration: " << rock.getFormattedTotalDuration() << "\n";
    // Expected:
    // Playlist: Rock Classics (3 songs)
    // Total duration: 20:28

    // Find a song
    Song* found = rock.findSong("Hotel California");
    if (found) {
        std::cout << "Found: " << found->getTitle() << " by " << found->getArtist() << "\n";
        // Expected: Found: Hotel California by Eagles
    }

    // Remove a song
    rock.removeSong(1);
    std::cout << "After remove: " << rock.getCount() << " songs\n";
    // Expected: After remove: 2 songs

    // Add another song
    Song s4("Imagine", "John Lennon", 183);
    rock.addSong(s4);
    std::cout << "After add: " << rock.getCount() << " songs\n";
    // Expected: After add: 3 songs

    // Copy playlist (deep copy)
    Playlist rockCopy(rock);
    rockCopy.setName("Rock Copy");
    rockCopy.removeSong(0);
    std::cout << "Original: " << rock.getCount() << ", Copy: " << rockCopy.getCount() << "\n";
    // Expected: Original: 3, Copy: 2

    // Create music library
    MusicLibrary lib("John");
    Playlist& favorites = lib.createPlaylist("Favorites");
    favorites.addSong(Song("Sweet Child O' Mine", "Guns N' Roses", 356));
    favorites.addSong(Song("November Rain", "Guns N' Roses", 537));

    lib.addPlaylist(rock);

    std::cout << "\nLibrary: " << lib.getOwnerName() << "\n";
    std::cout << "Playlists: " << lib.getPlaylistCount() << "\n";
    std::cout << "Total songs: " << lib.getTotalSongCount() << "\n";
    std::cout << "Total duration: " << lib.getTotalDuration() << " seconds\n";
    // Expected:
    // Library: John
    // Playlists: 2
    // Total songs: 5
    // Total duration: 1822 seconds

    // Find playlist
    Playlist* p = lib.findPlaylist("Favorites");
    if (p) {
        std::cout << "Found playlist: " << p->getName() << "\n";
        // Expected: Found playlist: Favorites
    }

    lib.removePlaylist("Rock Classics");
    std::cout << "After removal: " << lib.getPlaylistCount() << " playlists\n";
    // Expected: After removal: 1 playlists

    // Final stats
    std::cout << "\nSong count: " << Song::getSongCount() << "\n";
    std::cout << "Playlists created: " << Playlist::getTotalPlaylistsCreated() << "\n";

    return 0;
}