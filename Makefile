CXX=g++
INC=-I include
TARGET=bin/SFML-QuadTree.exe
LIBS=-lsfml-graphics -lsfml-window -lsfml-system
LIBSDLL=-ltest $(LIBS)
SRCS=$(wildcard src/*.cpp)
OBJS=$(SRCS:.cpp=.o)
OBJSDLL=$(filter-out src/main.o, $(OBJS))
CFLAGS=-std=c++17 -Wall -Os
SFMLINC=-I C:\Compilers\SFML-2.5.1\include
SFMLLIB=-L C:\Compilers\SFML-2.5.1\lib
QTLIB=$(SFMLLIB) -L lib/
TARGETLIB=bin/test.dll
TARGETDLLEXE=bin/testdll.exe
.PHONY: all clean makedll makedllexe

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LIBS) $(CFLAGS) $(SFMLINC) $(SFMLLIB)
.cpp.o:
	$(CXX) -c $< -o $@ $(INC) $(CFLAGS) $(SFMLINC) $(SFMLLIB)

makedll: $(TARGETLIB)

$(TARGETLIB): $(OBJSDLL)
	$(CXX) -shared -o $@ $(OBJSDLL) $(LIBS) $(SFMLINC) $(SFMLLIB)
.cpp.o:
	$(CXX) -c $< -o $@ $(INC) $(CFLAGS) $(SFMLINC) $(SFMLLIB)


makedllexe: $(TARGETDLLEXE)

$(TARGETDLLEXE):
	$(CXX) src\main.o -o $@ $(LIBSDLL) $(CFLAGS) $(SFMLINC) $(QTLIB)

clean:
	rm -rf $(OBJS)
	rm -rf $(TARGET)
	rm -rf $(TARGETDLLEXE)