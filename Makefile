CXX = g++
LDFLAGS = -lX11 -lGL -lpthread -lpng -lstdc++fs
CXXFLAGS = -std=c++14 -Wall -Wextra -Wpedantic -c

TARGET = main
SRCDIR = src/
OBJDIR = obj/

HPPS = $(wildcard $(SRCDIR)*.hpp)
CPPS = $(wildcard $(SRCDIR)*.cpp)
OBJS = $(wildcard $(OBJDIR)*)

.PHONEY: dirs all clean

all: dirs $(TARGET)

dirs:
	mkdir -p $(OBJDIR)

clean:
	rm -f $(TARGET) $(OBJS) && rmdir $(OBJDIR)

$(TARGET): obj/main.o obj/point.o obj/shape.o
	$(CXX) -o $@ $^ $(LDFLAGS)

obj/main.o: src/main.cpp $(HPPS)
	$(CXX) -o $@ $< $(CXXFLAGS)

obj/point.o: src/point.cpp src/point.hpp
	$(CXX) -o $@ $< $(CXXFLAGS)

obj/shape.o: src/shape.cpp src/shape.hpp
	$(CXX) -o $@ $< $(CXXFLAGS)
