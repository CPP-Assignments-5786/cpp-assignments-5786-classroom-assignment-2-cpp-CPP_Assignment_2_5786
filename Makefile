CXX=clang++
CXXFLAGS=-std=c++23 -Werror -Wsign-conversion
TIDY_FLAGS=-checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-* --warnings-as-errors=*

SOURCES=Song.cpp Playlist.cpp MusicLibrary.cpp
OBJECTS=$(subst .cpp,.o,$(SOURCES))

all: demo
	./demo

demo: main.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o demo

test: TestRunner.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o test
	./test

student_test: StudentTestRunner.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o student_test
	@count=$$(./student_test -ltc | grep -c "^[^[]"); \
	if [ $$count -lt 20 ]; then \
		echo "ERROR: StudentTest.cpp must contain at least 20 test cases (found $$count)"; \
		exit 1; \
	fi

TestRunner.o: test.cpp Song.hpp Playlist.hpp MusicLibrary.hpp doctest.h
	$(CXX) $(CXXFLAGS) --compile test.cpp -o TestRunner.o

StudentTestRunner.o: StudentTest.cpp $(wildcard *.hpp) doctest.h
	$(CXX) $(CXXFLAGS) --compile StudentTest.cpp -o StudentTestRunner.o

%.o: %.cpp
	$(CXX) $(CXXFLAGS) --compile $< -o $@

Song.o: Song.cpp Song.hpp

Playlist.o: Playlist.cpp Playlist.hpp Song.hpp

MusicLibrary.o: MusicLibrary.cpp MusicLibrary.hpp Playlist.hpp Song.hpp

main.o: main.cpp Song.hpp Playlist.hpp MusicLibrary.hpp

tidy:
	clang-tidy *.cpp $(TIDY_FLAGS) -- $(CXXFLAGS)

clean:
	rm -f *.o demo test student_test

.PHONY: all test tidy student_test clean