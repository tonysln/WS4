CC=g++
CFLAGS=-c -Wall -std=c++20
LDFLAGS=
LIBFLAGS=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
SOURCES=WS4.cpp gfx_init.cpp data_proc.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=WS4
BINDIR=/usr/bin


all: $(SOURCES) $(EXECUTABLE)
        
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(LIBFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@ $(LIBFLAGS)

clean:
	rm *.o $(EXECUTABLE)
