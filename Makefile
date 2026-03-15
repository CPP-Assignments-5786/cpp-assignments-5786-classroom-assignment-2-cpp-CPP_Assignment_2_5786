CXX=clang++
CXXFLAGS=-std=c++23 -Werror -Wsign-conversion
TIDY_FLAGS=-checks='*,-fuchsia-*,-llvm-header-guard,-misc-include-cleaner' --warnings-as-errors='*'
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
	./student_test --count | grep -q "test cases" && test $$(./student_test --count 2>&1 | grep -oP '\d+(?= test)' | head -1) -ge 20 || (echo "ERROR: StudentTest.cpp must contain at least 20 test cases" && exit 1)

TestRunner.o: test.cpp Song.hpp Playlist.hpp MusicLibrary.hpp doctest.h
	$(CXX) $(CXXFLAGS) --compile test.cpp -o TestRunner.o

StudentTestRunner.o: StudentTest.cpp Song.hpp Playlist.hpp MusicLibrary.hpp doctest.h
	$(CXX) $(CXXFLAGS) --compile StudentTest.cpp -o StudentTestRunner.o

%.o: %.cpp
	$(CXX) $(CXXFLAGS) --compile $< -o $@

Song.o: Song.cpp Song.hpp

Playlist.o: Playlist.cpp Playlist.hpp Song.hpp

MusicLibrary.o: MusicLibrary.cpp MusicLibrary.hpp Playlist.hpp Song.hpp

main.o: main.cpp Song.hpp Playlist.hpp MusicLibrary.hpp

tidy:
	clang-tidy $(SOURCES) main.cpp test.cpp $(TIDY_FLAGS) -- $(CXXFLAGS)

clean:
	rm -f *.o demo test student_test
