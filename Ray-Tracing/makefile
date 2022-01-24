CXX=        g++
CXXFLAGS=   -g -Wall -std=gnu++11
LDFLAGS=
SHELL=      bash
PROGRAMS=   generateppm
SOURCES=    generateppm.cpp
OBJECTS=    $(SOURCES:.cpp .txt .ppm)

all:        $(PROGRAMS)

clean:
	rm -f $(PROGRAMS) $(OBJECTS)
	rm -f example.ppm
	rm -f example.txt

test:       $(PROGRAMS)
	./generateppm