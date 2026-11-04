CXX ?= g++
CXXFLAGS ?= -std=c++17 -Wall -pthread -Iinclude -Itests
LIB := $(wildcard src/*.cpp)

all: forge_tests forge play

forge_tests: $(LIB) $(wildcard tests/*.cpp) $(wildcard include/*.h)
	$(CXX) $(CXXFLAGS) $(LIB) tests/*.cpp -o $@

forge: $(LIB) app/main.cpp $(wildcard include/*.h)
	$(CXX) $(CXXFLAGS) $(LIB) app/main.cpp -o $@

play: $(LIB) app/play.cpp $(wildcard include/*.h)
	$(CXX) $(CXXFLAGS) $(LIB) app/play.cpp -o $@

clean:
	rm -f forge forge_tests play forge.exe forge_tests.exe play.exe
