/**
 * @file Playlist.hpp
 * @brief Header file for the Playlist class
 *
 * This file contains the declaration of the Playlist class which manages
 * a dynamic array of Song pointers.
 *
 * Students must implement the corresponding Playlist.cpp file.
 *
 * Topics covered:
 * - Dynamic memory allocation (new/delete)
 * - Array destruction (delete[])
 * - Constructors (default, parameterized, copy)
 * - Destructor with proper cleanup
 * - Static members
 */

#ifndef PLAYLIST_HPP
#define PLAYLIST_HPP

#include "Song.hpp"
#include <string>
#include <iostream>

namespace music {

    class Playlist {
    private:
        std::string name;
        Song** songs;  // Dynamic array of Song pointers
        int capacity;           // Maximum number of songs
        int count;              // Current number of songs

        // Static member to track total playlists created (never decremented)
        static int totalPlaylistsCreated;

        /**
         * @brief Helper method to resize the internal array when full
         * Should double the capacity.
         * Must be implemented in Playlist.cpp.
         */
        void resize();

    public:
        // ============ Constructors ============

        /**
         * @brief Default constructor
         * Creates an empty playlist named "Untitled" with initial capacity of 4.
         * Should increment totalPlaylistsCreated.
         */
        Playlist();

        /**
         * @brief Parameterized constructor
         * @param name The playlist name
         * @param initialCapacity Initial capacity (default: 4)
         * @throws std::invalid_argument if initialCapacity <= 0
         * Should increment totalPlaylistsCreated.
         */
        explicit Playlist(const std::string& name, int initialCapacity = 4);

        /**
         * @brief Copy constructor - performs deep copy
         * @param other The playlist to copy from
         * Should increment totalPlaylistsCreated.
         * Must create new Song objects (deep copy).
         */
        Playlist(const Playlist& other);
        Playlist& operator=(const Playlist& other); // Copy assignment
        Playlist(Playlist&& other) noexcept;        // Move constructor
        Playlist& operator=(Playlist&& other) noexcept; // Move assignment

        /**
         * @brief Destructor
         * Must delete all Song objects AND the array itself.
         * This is crucial for valgrind testing!
         */
        ~Playlist();

        // ============ Getters (inline implementations) ============

        /**
         * @brief Get the playlist name
         * @return The name as a string
         * MUST be implemented inline.
         */
        std::string getName() const {
            return name;
        }

        /**
         * @brief Get the current number of songs
         * @return The count
         * MUST be implemented inline.
         */
        int getCount() const {
            return count;
        }

        /**
         * @brief Get the current capacity
         * @return The capacity
         * MUST be implemented inline.
         */
        int getCapacity() const {
            return capacity;
        }

        /**
         * @brief Check if playlist is empty
         * @return true if no songs
         * MUST be implemented inline.
         */
        bool isEmpty() const {
            return count == 0;
        }

        // ============ Setters (outline implementations) ============

        /**
         * @brief Set the playlist name
         * @param name New name
         * Must be implemented in Playlist.cpp.
         */
        void setName(const std::string& name);

        // ============ Static methods ============

        /**
         * @brief Get total number of playlists ever created
         * @return The total count
         * Must be implemented in Playlist.cpp.
         */
        static int getTotalPlaylistsCreated();

        // ============ Song management ============

        /**
         * @brief Add a song to the playlist (creates a copy)
         * @param song The song to add
         * If capacity is reached, should call resize().
         * Must be implemented in Playlist.cpp.
         */
        void addSong(const Song& song);

        /**
         * @brief Remove a song by index
         * @param index The index to remove
         * @return true if removed, false if index invalid
         * Must shift remaining songs to fill the gap.
         * Must delete the removed Song object.
         * Must be implemented in Playlist.cpp.
         */
        bool removeSong(int index);

        /**
         * @brief Remove a song by title and artist
         * @param title The song title
         * @param artist The artist name
         * @return true if found and removed, false otherwise
         * Must be implemented in Playlist.cpp.
         */
        bool removeSong(const std::string& title, const std::string& artist);

        /**
         * @brief Find a song by title
         * @param title The title to search for
         * @return Pointer to the song if found, nullptr otherwise
         * Must be implemented in Playlist.cpp.
         */
        Song* findSong(const std::string& title) const;

        /**
         * @brief Get total duration of all songs
         * @return Total duration in seconds
         * Must be implemented in Playlist.cpp.
         */
        int getTotalDuration() const;

        /**
         * @brief Get formatted total duration as "H:MM:SS" or "M:SS"
         * @return Formatted string
         * If total duration is one hour or more, format as "H:MM:SS" (e.g., "1:05:30").
         * Otherwise, format as "M:SS" (e.g., "20:28").
         * Seconds and minutes parts should always be zero-padded to two digits.
         * Must be implemented in Playlist.cpp.
         */
        std::string getFormattedTotalDuration() const;

        /**
         * @brief Clear all songs from the playlist
         * Must delete all Song objects.
         * Must be implemented in Playlist.cpp.
         */
        void clear();

    };

} // namespace music

#endif // PLAYLIST_HPP
