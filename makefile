CC = gcc
CXX = g++
WARNINGFLAGS = -Wall -Wextra
LDFLAGSBASE = 
CFLAGSBASE = -std=gnu11 -pthread
CXXFLAGSBASE = -std=gnu++11 -pthread
FLAGSBASE = -O2 -DNDEBUG
DEBUGFLAGSBASE = -g -DDEBUG
LIBS = -lpthread
ifdef DEBUG
LDFLAGS = $(LDFLAGSBASE) $(DEBUGFLAGSBASE) $(WARNINGFLAGS)
CFLAGS = $(CFLAGSBASE) $(DEBUGFLAGSBASE) $(WARNINGFLAGS)
CXXFLAGS = $(CXXFLAGSBASE) $(DEBUGFLAGSBASE) $(WARNINGFLAGS)
else
LDFLAGS = $(LDFLAGSBASE) $(FLAGSBASE) $(WARNINGFLAGS)
CFLAGS = $(CFLAGSBASE) $(FLAGSBASE) $(WARNINGFLAGS)
CXXFLAGS = $(CXXFLAGSBASE) $(FLAGSBASE) $(WARNINGFLAGS)
endif
export

OBJECTS = $(patsubst %.cpp,%.o,$(notdir $(wildcard *.cpp)))

all: Othello

Othello: $(OBJECTS)
        $(CXX) $(LDFLAGS) -o Othello $(OBJECTS) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
        @rm -rf Othello *.o

.PHONY: clean
