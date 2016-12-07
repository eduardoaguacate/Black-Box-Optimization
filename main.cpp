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

int main(int argc, const char * argv[]) {

   std::string scenario_path = "../Scenarios/00.xml";
   WindScenario wscenario(scenario_path);
   KusiakLayoutEvaluator evaluator;
   evaluator.initialize(wscenario);

   using namespace std::placeholders;
  //  std::vector<individual> population = initialization::initialization_2(evaluator,wscenario);
  //  std::cout << "1" << std::endl;
  //  auto selection = selection::selection_1(population);
   // This is how you use the evolutionary_algorithm

   auto select_stub = [](std::vector<individual>& pop){
     std::vector<std::vector<individual>::iterator> parents;
     for (auto it = pop.begin(); it != pop.end(); ++it){
       parents.push_back(it);
     }
     return parents;
   };

   individual best = evolutionary_algorithm(
      evaluator,
      wscenario,
      initialization::initialization_2,
      select_stub,
      recombination::crossover,
      std::bind(mutation::creep, 0.5, wscenario.width, wscenario.height, _1, _2),
      replacement::replacement_1,
      1);



   std::cout << best.fitness << std::endl;
}
