CC=g++
CFLAGS =-Wall -g -w -std=c++0x
OPTFLAGS=-O2
INCLUDES=-I$(PWD)

SOURCES=API/tinyxml2.cpp API/WindScenario.cpp API/WindFarmLayoutEvaluator.cpp API/KusiakLayoutEvaluator.cpp

OBJECTS=$(SOURCES:.cpp=.o)

main:$(OBJECTS)
		$(CC) $(CFLAGS) -o main $(OBJECTS) main.cpp $(INCLUDES) $(OPTFLAGS)

.cpp.o:
		$(CC) $(CFLAGS) -c $< -o $@ -w $(INCLUDES) $(OPTFLAGS)

clean:
	 rm $(OBJECTS) main
