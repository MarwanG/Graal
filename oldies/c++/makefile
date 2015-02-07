

CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=MurmurHash3.cpp hll.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=exec

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
			$(CC) $(LDFLAGS) $(OBJECTS) -o $@
		
.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o exec
