CC=g++
INCLUDE=
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.cc 
OBJECTS=$(SOURCES:.cc=.o)
EXECUTABLE=test

all: $(SOURCES) $(EXECUTABLE)
		
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS)  -o $@

.cc.o:
	$(CC) $(CFLAGS) $(INCLUDE) $< -o $@

clean :
	rm -rf $(OBJECTS) $(EXECUTABLE)
