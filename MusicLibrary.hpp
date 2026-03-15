/**
 * @file MusicLibrary.hpp
 * @brief Header file for the MusicLibrary class
 *
 * This file contains the declaration of the MusicLibrary class which manages
 * a collection of Playlists. This is a singleton-like pattern using static methods.
 *
 * Students must implement the corresponding MusicLibrary.cpp file.
 *
 * Topics covered:
 * - Static members and methods
 * - Dynamic array management
 * - Destructor with nested object cleanup
 */

#ifndef MUSICLIBRARY_HPP
#define MUSICLIBRARY_HPP

#include "Playlist.hpp"
#include <string>
#include <iostream>

namespace music {

    class MusicLibrary {
    private:
        std::string ownerName;
        Playlist** playlists;   // Dynamic array of Playlist pointers
        int capacity;
        int count;

        // Static member for library-wide statistics
        static int totalSongsAddedEver;  // Tracks total songs ever added across all libraries

        /**
         * @brief Helper to resize the playlists array
         * Must be implemented in MusicLibrary.cpp.
         */
        void resize();

    public:
        // ============ Constructors ============

        /**
         * @brief Default constructor
         * Creates a library with owner "Anonymous" and initial capacity of 2.
         */
        MusicLibrary();

        /**
         * @brief Parameterized constructor
         * @param ownerName The owner's name
         * @param initialCapacity Initial playlist capacity (default: 2)
         * @throws std::invalid_argument if initialCapacity <= 0
         */
        explicit MusicLibrary(const std::string& ownerName, int initialCapacity = 2);

        /**
         * @brief Copy constructor - deep copy
         * @param other The library to copy from
         */
        MusicLibrary(const MusicLibrary& other);

        /**
         * @brief Destructor
         * Must delete all Playlist objects (which in turn delete their Songs).
         * This tests proper cascading destruction!
         */
        ~MusicLibrary();

        // ============ Getters (inline) ============

        /**
         * @brief Get owner name
         * MUST be inline.
         */
        inline std::string getOwnerName() const {
            return ownerName;
        }

        /**
         * @brief Get number of playlists
         * MUST be inline.
         */
        inline int getPlaylistCount() const {
            return count;
        }

        // ============ Setters (outline) ============

        /**
         * @brief Set owner name
         * Must be implemented in MusicLibrary.cpp.
         */
        void setOwnerName(const std::string& name);

        // ============ Static methods ============

        /**
         * @brief Get total songs ever added across all libraries
         * @return The total count
         * Must be implemented in MusicLibrary.cpp.
         */
        static int getTotalSongsAddedEver();

        /**
         * @brief Increment the total songs counter
         * Called internally when adding songs.
         * Must be implemented in MusicLibrary.cpp.
         */
        static void incrementTotalSongs();

        // ============ Playlist management ============

        /**
         * @brief Create and add a new empty playlist
         * @param name The playlist name
         * @return Reference to the created playlist
         * Must be implemented in MusicLibrary.cpp.
         */
        Playlist& createPlaylist(const std::string& name);

        /**
         * @brief Add an existing playlist (creates a copy)
         * @param playlist The playlist to add
         * Must be implemented in MusicLibrary.cpp.
         */
        void addPlaylist(const Playlist& playlist);

        /**
         * @brief Remove a playlist by index
         * @param index The index
         * @return true if removed, false if invalid index
         * Must be implemented in MusicLibrary.cpp.
         */
        bool removePlaylist(int index);

        /**
         * @brief Remove a playlist by name
         * @param name The playlist name
         * @return true if found and removed
         * Must be implemented in MusicLibrary.cpp.
         */
        bool removePlaylist(const std::string& name);

        /**
         * @brief Find a playlist by name
         * @param name The name to search for
         * @return Pointer to playlist if found, nullptr otherwise
         * Must be implemented in MusicLibrary.cpp.
         */
        Playlist* findPlaylist(const std::string& name) const;

        /**
         * @brief Get total duration of all songs in all playlists
         * @return Total duration in seconds
         * Must be implemented in MusicLibrary.cpp.
         */
        int getTotalDuration() const;

        /**
         * @brief Get total number of songs across all playlists
         * @return Total song count
         * Must be implemented in MusicLibrary.cpp.
         */
        int getTotalSongCount() const;

        /**
         * @brief Clear all playlists
         * Must delete all Playlist objects.
         * Must be implemented in MusicLibrary.cpp.
         */
        void clear();

    };

} // namespace music

#endif // MUSICLIBRARY_HPP

