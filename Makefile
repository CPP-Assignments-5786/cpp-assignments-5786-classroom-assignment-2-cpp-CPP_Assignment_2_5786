#!make -f

CXX=g++
CXXFLAGS=-std=c++17 -Werror -Wsign-conversion
SOURCES=Song.cpp Playlist.cpp MusicLibrary.cpp
OBJECTS=$(subst .cpp,.o,$(SOURCES))

all: demo
	./demo

demo: main.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o demo

test: TestRunner.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o test
	./test

TestRunner.o: test.cpp Song.hpp Playlist.hpp MusicLibrary.hpp doctest.h
	$(CXX) $(CXXFLAGS) --compile test.cpp -o TestRunner.o

%.o: %.cpp
	$(CXX) $(CXXFLAGS) --compile $< -o $@

Song.o: Song.cpp Song.hpp

Playlist.o: Playlist.cpp Playlist.hpp Song.hpp

MusicLibrary.o: MusicLibrary.cpp MusicLibrary.hpp Playlist.hpp Song.hpp

main.o: main.cpp Song.hpp Playlist.hpp MusicLibrary.hpp

clean:
	rm -f *.o demo test
