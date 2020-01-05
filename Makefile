CXX=g++
INC=-I include
TARGET=bin/SFML-QuadTree.exe
LIBS=-lsfml-graphics -lsfml-window -lsfml-system
#SRCS=src/main.cpp src/camera.cpp src/checkColor.cpp src/Settlement.cpp
SRCS=$(wildcard src/*.cpp)
OBJS=$(SRCS:.cpp=.o)
CFLAGS=-std=c++17 -Wall -Os
SFMLINC=-I C:\Compilers\SFML-2.5.1\include
SFMLLIB=-L C:\Compilers\SFML-2.5.1\lib
.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LIBS) $(CFLAGS) $(SFMLINC) $(SFMLLIB)
.cpp.o:
	$(CXX) -c $< -o $@ $(INC) $(CFLAGS) $(SFMLINC) $(SFMLLIB)

clean:
	rm -rf $(OBJS)