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

   std::string scenario_path = "../Scenarios/00.xml";
   WindScenario wscenario(scenario_path);
   KusiakLayoutEvaluator evaluator;
   evaluator.initialize(wscenario);

   using namespace std::placeholders;
  //  std::vector<individual> population = initialization::initialization_2(evaluator,wscenario);
  //  std::cout << "1" << std::endl;
  //  auto selection = selection::selection_1(population);
   // This is how you use the evolutionary_algorithm

   individual best = evolutionary_algorithm(
      evaluator,
      wscenario,
      initialization::initialization_2,
      std::bind(selection::selection_1,_1,30),
      recombination::crossover,
      std::bind(mutation::creep, 0.5, wscenario.width, wscenario.height, _1, _2),
      replacement::replacement_1,
      100);



   std::cout << "Best " <<best.fitness << std::endl;
}
