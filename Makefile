CXX = g++
# LD = ld
LDFLAGS = -lX11 -lGL -lpthread -lpng -lstdc++fs
CXXFLAGS = -std=c++14 -Wall -Wextra -Wpedantic -c
TARGET = main

HEADERS = src/shape.hpp src/screen.hpp src/domain.hpp src/mapRange.hpp src/transform.hpp

all: $(TARGET)

$(TARGET): obj/main.o obj/point.o obj/shape.o
	$(CXX) -o $(TARGET) $^ $(LDFLAGS)

obj/main.o: src/main.cpp $(HEADERS)
	$(CXX) -o $@ $< $(CXXFLAGS)

obj/point.o: src/point.cpp src/point.hpp
	$(CXX) -o $@ $< $(CXXFLAGS)

obj/shape.o: src/shape.cpp src/shape.hpp
	$(CXX) -o $@ $< $(CXXFLAGS)