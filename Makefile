CXX = g++
LDFLAGS = -lX11 -lGL -lpthread -lpng -lstdc++fs
CXXFLAGS = -std=c++14 -Wall -Wextra -Wpedantic
TARGET = main

HEADERS = src/shape.hpp src/screen.hpp src/domain.hpp src/mapRange.hpp src/transform.hpp

all: $(TARGET)

$(TARGET): src/main.cpp $(HEADERS)
	$(CXX) -o $@ $< $(CXXFLAGS) $(LDFLAGS)