/**
 * @file Song.hpp
 * @brief Header file for the Song class
 *
 * This file contains the declaration of the Song class which represents
 * a music track with title, artist, and duration.
 *
 * Students must implement the corresponding Song.cpp file.
 *
 * Topics covered:
 * - Constructors (default, parameterized, copy)
 * - Destructor
 * - Inline vs outline implementations
 * - Static members
 */

#ifndef SONG_HPP
#define SONG_HPP

#include <string>
#include <iostream>

namespace music {

    class Song {
    private:
        std::string title;
        std::string artist;
        int durationSeconds;  // Duration in seconds

        // Static member to track total number of Song objects created
        static int songCount;

    public:
        // ============ Constructors ============

        /**
         * @brief Default constructor
         * Creates an "Unknown" song with 0 duration.
         * Should increment songCount.
         */
        Song();

        /**
         * @brief Parameterized constructor
         * @param title The song title
         * @param artist The artist name
         * @param durationSeconds Duration in seconds (must be >= 0)
         * @throws std::invalid_argument if durationSeconds is negative
         * Should increment songCount.
         */
        Song(const std::string& title, const std::string& artist, int durationSeconds);

        /**
         * @brief Copy constructor
         * @param other The song to copy from
         * Should increment songCount.
         */
        Song(const Song& other);

        /**
         * @brief Destructor
         * Should decrement songCount.
         */
        ~Song();

        // ============ Getters (inline implementations) ============

        /**
         * @brief Get the song title
         * @return The title as a string
         * MUST be implemented inline in this header file.
         */
        inline std::string getTitle() const {
            return title;
        }

        /**
         * @brief Get the artist name
         * @return The artist as a string
         * MUST be implemented inline in this header file.
         */
        inline std::string getArtist() const {
            return artist;
        }

        /**
         * @brief Get the duration in seconds
         * @return Duration in seconds
         * MUST be implemented inline in this header file.
         */
        inline int getDuration() const {
            return durationSeconds;
        }

        // ============ Setters (outline implementations) ============

        /**
         * @brief Set the song title
         * @param title New title
         * Must be implemented in Song.cpp (outline).
         */
        void setTitle(const std::string& title);

        /**
         * @brief Set the artist name
         * @param artist New artist name
         * Must be implemented in Song.cpp (outline).
         */
        void setArtist(const std::string& artist);

        /**
         * @brief Set the duration
         * @param seconds New duration in seconds
         * @throws std::invalid_argument if seconds is negative
         * Must be implemented in Song.cpp (outline).
         */
        void setDuration(int seconds);

        // ============ Static methods ============

        /**
         * @brief Get the total count of Song objects currently in memory
         * @return The current song count
         * Must be implemented in Song.cpp.
         */
        static int getSongCount();

        // ============ Utility methods ============

        /**
         * @brief Get duration formatted as "MM:SS"
         * @return Formatted duration string
         * Example: 185 seconds -> "3:05"
         * Must be implemented in Song.cpp.
         */
        std::string getFormattedDuration() const;

    };

} // namespace music

#endif // SONG_HPP

