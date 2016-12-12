/*  main.cpp
 *
 *   This is the class in which the evolutionary algorithm is going to be run.
 *   Version: 1.0.0
 */

//STL libraries
#include <iostream>

//API libraries
#include "API/WindScenario.h"
#include "API/KusiakLayoutEvaluator.h"

//Project's libraries
#include "structures.hpp"
#include "initialization.hpp"
#include "selection.hpp"
#include "recombination.hpp"
#include "mutation.hpp"
#include "replacement.hpp"
#include "evolutionary_algorithm.hpp"
#include <time.h>
#include <stdlib.h>

int main(int argc, const char * argv[]) {

   srand(time(NULL));

   WindScenario wscenario(argv[1]);
   KusiakLayoutEvaluator evaluator;
   evaluator.initialize(wscenario);

   
   

   using namespace std::placeholders;
   individual best = evolutionary_algorithm(
      evaluator,
      wscenario,
      initialization::initialization_1,
      std::bind(selection::selection_1, _1, 30),
      recombination::crossover,
      std::bind(mutation::creep, 1000.0, _1, _2),
      replacement::replacement_1,
      10);
   
   std::cout << "Best " << best.fitness << std::endl;
}
