/**
 * @file test.cpp
 * @brief Unit tests for Music Library Management System using doctest
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <fstream>
#include "Song.hpp"
#include "Playlist.hpp"
#include "MusicLibrary.hpp"

using namespace music;

// ==================== SONG CLASS TESTS ====================

TEST_CASE("Song - Default Constructor") {
    Song s;
    CHECK(s.getTitle() == "Unknown");
    CHECK(s.getArtist() == "Unknown");
    CHECK(s.getDuration() == 0);
}

TEST_CASE("Song - Parameterized Constructor") {
    Song s("Title", "Artist", 180);
    CHECK(s.getTitle() == "Title");
    CHECK(s.getArtist() == "Artist");
    CHECK(s.getDuration() == 180);
}

TEST_CASE("Song - Copy Constructor") {
    Song s1("Title", "Artist", 200);
    Song s2(s1);
    CHECK(s2.getTitle() == s1.getTitle());
    CHECK(s2.getArtist() == s1.getArtist());
    CHECK(s2.getDuration() == s1.getDuration());
}

TEST_CASE("Song - Setters") {
    Song s;
    s.setTitle("New Title");
    s.setArtist("New Artist");
    s.setDuration(300);
    CHECK(s.getTitle() == "New Title");
    CHECK(s.getArtist() == "New Artist");
    CHECK(s.getDuration() == 300);
}

TEST_CASE("Song - Negative Duration Throws") {
    CHECK_THROWS_AS(Song("Bad", "Song", -1), std::invalid_argument);

    Song s;
    CHECK_THROWS_AS(s.setDuration(-10), std::invalid_argument);
}

TEST_CASE("Song - Formatted Duration") {
    Song s1("A", "B", 65);   // 1:05
    CHECK(s1.getFormattedDuration() == "1:05");

    Song s2("A", "B", 3600); // 60:00
    CHECK(s2.getFormattedDuration() == "60:00");

    Song s3("A", "B", 0);
    CHECK(s3.getFormattedDuration() == "0:00");
}

// ==================== PLAYLIST CLASS TESTS ====================

TEST_CASE("Playlist - Default Constructor") {
    Playlist p;
    CHECK(p.getName() == "Untitled");
    CHECK(p.getCapacity() == 4);
    CHECK(p.getCount() == 0);
    CHECK(p.isEmpty());
}

TEST_CASE("Playlist - Parameterized Constructor") {
    Playlist p("My Playlist", 8);
    CHECK(p.getName() == "My Playlist");
    CHECK(p.getCapacity() == 8);
}

TEST_CASE("Playlist - Invalid Capacity Throws") {
    CHECK_THROWS_AS(Playlist("Bad", 0), std::invalid_argument);
    CHECK_THROWS_AS(Playlist("Bad", -5), std::invalid_argument);
}

TEST_CASE("Playlist - Add Song") {
    Playlist p("Test");
    Song s("Title", "Artist", 100);

    p.addSong(s);
    CHECK(p.getCount() == 1);
    CHECK_FALSE(p.isEmpty());
}

TEST_CASE("Playlist - Resize on Overflow") {
    Playlist p("Test", 2);
    p.addSong(Song("A", "A", 100));
    p.addSong(Song("B", "B", 100));
    CHECK(p.getCapacity() == 2);

    p.addSong(Song("C", "C", 100));  // triggers resize
    CHECK(p.getCapacity() == 4);
    CHECK(p.getCount() == 3);
}

TEST_CASE("Playlist - Remove Song by Index") {
    Playlist p("Test");
    p.addSong(Song("A", "A", 100));
    p.addSong(Song("B", "B", 100));

    CHECK(p.removeSong(0));
    CHECK(p.getCount() == 1);

    CHECK_FALSE(p.removeSong(10));  // invalid index
}

TEST_CASE("Playlist - Remove Song by Title/Artist") {
    Playlist p("Test");
    p.addSong(Song("Hello", "Adele", 100));
    p.addSong(Song("World", "Someone", 100));

    CHECK(p.removeSong("Hello", "Adele"));
    CHECK(p.getCount() == 1);
    CHECK_FALSE(p.removeSong("Nonexistent", "Artist"));
}

TEST_CASE("Playlist - Find Song") {
    Playlist p("Test");
    p.addSong(Song("Hello", "Adele", 100));

    Song* found = p.findSong("Hello");
    CHECK(found != nullptr);
    CHECK(found->getTitle() == "Hello");

    CHECK(p.findSong("Nonexistent") == nullptr);
}

TEST_CASE("Playlist - Total Duration") {
    Playlist p("Test");
    p.addSong(Song("A", "A", 100));
    p.addSong(Song("B", "B", 200));

    CHECK(p.getTotalDuration() == 300);
}

TEST_CASE("Playlist - Copy Constructor (Deep Copy)") {
    Playlist p1("Original");
    p1.addSong(Song("A", "B", 100));

    Playlist p2(p1);
    p2.setName("Copy");
    p2.removeSong(0);

    CHECK(p1.getName() == "Original");
    CHECK(p1.getCount() == 1);
    CHECK(p2.getName() == "Copy");
    CHECK(p2.getCount() == 0);
}

TEST_CASE("Playlist - Clear") {
    Playlist p("Test");
    p.addSong(Song("A", "A", 100));
    p.addSong(Song("B", "B", 100));

    p.clear();
    CHECK(p.getCount() == 0);
    CHECK(p.isEmpty());
}

// ==================== MUSICLIBRARY CLASS TESTS ====================

TEST_CASE("MusicLibrary - Default Constructor") {
    MusicLibrary lib;
    CHECK(lib.getOwnerName() == "Anonymous");
    CHECK(lib.getPlaylistCount() == 0);
}

TEST_CASE("MusicLibrary - Parameterized Constructor") {
    MusicLibrary lib("John", 5);
    CHECK(lib.getOwnerName() == "John");
}

TEST_CASE("MusicLibrary - Invalid Capacity Throws") {
    CHECK_THROWS_AS(MusicLibrary("Bad", 0), std::invalid_argument);
}

TEST_CASE("MusicLibrary - Create Playlist") {
    MusicLibrary lib("John");
    Playlist& p = lib.createPlaylist("My Playlist");

    CHECK(lib.getPlaylistCount() == 1);
    CHECK(p.getName() == "My Playlist");
}

TEST_CASE("MusicLibrary - Add Playlist") {
    MusicLibrary lib("John");
    Playlist p("External");
    p.addSong(Song("A", "B", 100));

    lib.addPlaylist(p);
    CHECK(lib.getPlaylistCount() == 1);
}

TEST_CASE("MusicLibrary - Remove Playlist by Index") {
    MusicLibrary lib("John");
    lib.createPlaylist("First");
    lib.createPlaylist("Second");

    CHECK(lib.removePlaylist(0));
    CHECK(lib.getPlaylistCount() == 1);
}

TEST_CASE("MusicLibrary - Remove Playlist by Name") {
    MusicLibrary lib("John");
    lib.createPlaylist("ToRemove");
    lib.createPlaylist("ToKeep");

    CHECK(lib.removePlaylist("ToRemove"));
    CHECK(lib.getPlaylistCount() == 1);
    CHECK_FALSE(lib.removePlaylist("Nonexistent"));
}

TEST_CASE("MusicLibrary - Find Playlist") {
    MusicLibrary lib("John");
    lib.createPlaylist("Favorites");

    Playlist* found = lib.findPlaylist("Favorites");
    CHECK(found != nullptr);
    CHECK(found->getName() == "Favorites");

    CHECK(lib.findPlaylist("Nonexistent") == nullptr);
}

TEST_CASE("MusicLibrary - Total Song Count") {
    MusicLibrary lib("John");
    Playlist& p1 = lib.createPlaylist("A");
    p1.addSong(Song("S1", "A", 100));
    p1.addSong(Song("S2", "A", 100));

    Playlist& p2 = lib.createPlaylist("B");
    p2.addSong(Song("S3", "A", 100));

    CHECK(lib.getTotalSongCount() == 3);
}

TEST_CASE("MusicLibrary - Total Duration") {
    MusicLibrary lib("John");
    Playlist& p = lib.createPlaylist("Test");
    p.addSong(Song("A", "A", 100));
    p.addSong(Song("B", "B", 200));

    CHECK(lib.getTotalDuration() == 300);
}

TEST_CASE("Playlist - Formatted Total Duration (MM:SS)") {
    Playlist p("Test");
    p.addSong(Song("A", "A", 100));
    p.addSong(Song("B", "B", 200));

    // 300 seconds = 5:00
    CHECK(p.getFormattedTotalDuration() == "5:00");
}

TEST_CASE("Playlist - Formatted Total Duration (HH:MM:SS)") {
    Playlist p("Test");
    p.addSong(Song("A", "A", 3600));
    p.addSong(Song("B", "B", 661));

    // 4261 seconds = 1 hour, 11 minutes, 1 second = 1:11:01
    CHECK(p.getFormattedTotalDuration() == "1:11:01");
}

TEST_CASE("MusicLibrary - Clear") {
    MusicLibrary lib("John");
    lib.createPlaylist("A");
    lib.createPlaylist("B");

    lib.clear();
    CHECK(lib.getPlaylistCount() == 0);
}

TEST_CASE("MusicLibrary - Copy Constructor (Deep Copy)") {
    MusicLibrary lib1("John");
    Playlist& p = lib1.createPlaylist("Favorites");
    p.addSong(Song("A", "B", 100));

    MusicLibrary lib2(lib1);
    lib2.setOwnerName("Jane");
    lib2.removePlaylist(0);

    CHECK(lib1.getOwnerName() == "John");
    CHECK(lib1.getPlaylistCount() == 1);
    CHECK(lib2.getOwnerName() == "Jane");
    CHECK(lib2.getPlaylistCount() == 0);
}

TEST_CASE("Student custom tests file exists") {
    std::ifstream f("StudentTest.cpp");
    CHECK_MESSAGE(f.good(), "StudentTest.cpp file must be created by the student");
}