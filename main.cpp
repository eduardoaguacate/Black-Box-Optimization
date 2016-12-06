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
#include "initialization.cpp"
#include "selection.hpp"
#include "recombination.hpp"
#include "mutation.hpp"
#include "replacement.cpp"
#include "evolutionary_algorithm.hpp"

int main(int argc, const char * argv[]) {
   string scenario_path = "Scenarios/00.xml";
   WindScenario wscenario(scenario_path);
   KusiakLayoutEvaluator evaluator;
   evaluator.initialize(wscenario);

   // this is just a stub, replace it once we have a real selection
  //  auto selection_stub = [](std::vector<individual>& population) {
  //     std::vector<std::vector<individual>::iterator> parents;
  //     for (auto it = population.begin(); it != population.end(); ++it)
  //     {
  //        parents.push_back(it);
  //     }
  //     return parents;
  //  };
   //
  //  // this is just a stub, replace it once we have a real selection
  //  auto replacement_stub = [](const std::vector<individual>& parents,
  //                             const std::vector<individual>& children) {
  //     return children;
  //  };
   //
  //  using namespace std::placeholders;
  //  // this is how you use the evolutionary_algorithm
  //  individual best = evolutionary_algorithm(
  //     evaluator,
  //     wscenario,
  //     initialization::initialization_2,
  //     selection_stub,
  //     recombination::crossover,
  //     std::bind(mutation::creep, 0.5, wscenario.width, wscenario.height, _1, _2),
  //     replacement_stub,
  //     100);

   //std::cout << best.fitness << std::endl;
}
