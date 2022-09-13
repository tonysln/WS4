CC=g++
CFLAGS=-c -Wall -std=c++11 
LDFLAGS=
LIBFLAGS=-lsfml-graphics -lsfml-window -lsfml-system
SOURCES=WS4.cpp
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

# install:
# 	#install -s $(EXECUTABLE) $(BINDIR)
# 	sudo cp -u $(EXECUTABLE) $(BINDIR)

# uninstall:
# 	sudo rm $(BINDIR)/$(EXECUTABLE)
