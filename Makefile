CC=g++
CFLAGS =-Wall -g -w -std=c++0x
OPTFLAGS=-O2
INCLUDES=-I$(PWD)

API=API/tinyxml2.cpp API/WindScenario.cpp API/WindFarmLayoutEvaluator.cpp API/KusiakLayoutEvaluator.cpp

EA=evolutionary_algorithm.cpp
functions=functions.cpp
initialization=initialization.cpp
mutation=mutation.cpp
random=Random.cpp
recombination=recombination.cpp
replacement=replacement.cpp
selection=selection.cpp


API_OBJECTS=$(API:.cpp=.o)
EA_OBJECT=$(EA:.cpp=.o)
FUNCTIONS_OBJECT=$(functions:.cpp=.o)
RANDOM_OBJECT=$(random:.cpp=.o)
INITIALIZATION_OBJECT=$(initialization:.cpp=.o)
MUTATION_OBJECT=$(mutation:.cpp=.o)
RECOMBINATION_OBJECT=$(recombination:.cpp=.o)
REPLACEMENT_OBJECT=$(replacement:.cpp=.o)
SELECTION_OBJECT=$(selection:.cpp=.o)

functions:$(API_OBJECTS)
		$(CC) $(CFLAGS) -c $ functions.cpp $(API_OBJECTS) functions.o   $(INCLUDES) $(OPTFLAGS)

random:
	$(CC) $(CFLAGS) -c random.o $(API_OBJECTS) $ random.cpp $(INCLUDES) $(OPTFLAGS)

initialization: $(FUNCTIONS_OBJECT)
	$(CC) $(CFLAGS) -c initialization.o $(FUNCTIONS_OBJECT) $ initialization.cpp $(INCLUDES) $(OPTFLAGS)

mutation: $(API_OBJECTS)
	$(CC) $(CFLAGS) -c mutation.o $(API_OBJECTS) $ mutation.cpp $(INCLUDES) $(OPTFLAGS)

recombination: $(API_OBJECTS)
	$(CC) $(CFLAGS) -c recombination.o $(API_OBJECTS) $ recombination.cpp $(INCLUDES) $(OPTFLAGS)

replacement: $(FUNCTIONS_OBJECT) $(RANDOM_OBJECT)
	$(CC) $(CFLAGS) -c replacement.o $(API_OBJECTS) $ replacement.cpp $(INCLUDES) $(OPTFLAGS)

selection: $(API_OBJECTS)
	$(CC) $(CFLAGS) -c selection.o $(API_OBJECTS) $ selection.cpp $(INCLUDES) $(OPTFLAGS)

evolutionary_algorithm:$(INITIALIZATION_OBJECT) $(SELECTION_OBJECT) $(MUTATION_OBJECT) $(RECOMBINATION_OBJECT) $(REPLACEMENT_OBJECT)
	$(CC) $(CFLAGS) -c evolutionary_algorithm.o $(API_OBJECTS) $ evolutionary_algorithm.cpp $(INCLUDES) $(OPTFLAGS)

main:$(EA_OBJECT)
		$(CC) $(CFLAGS) -o main.o $(API_OBJECTS) $ main.cpp $(INCLUDES) $(OPTFLAGS)

.cpp.o:
		$(CC) $(CFLAGS) -c $< -o $@ -w $(INCLUDES) $(OPTFLAGS)

clean:
	 rm $(OBJECTS) *.o
