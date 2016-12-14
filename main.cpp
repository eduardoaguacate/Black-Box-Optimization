/*  main.cpp
 *
 *   This is the class in which the evolutionary algorithm is going to be run.
 *   Version: 1.0.0
 */

//STL libraries
#include <iostream>
#include <string>

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
#include "statistical_comparison.hpp"
#include <time.h>
#include <stdlib.h>

int main(int argc, const char * argv[]) {

   srand(time(NULL));

   std::string arg1 = argv[1];
   if (arg1 == "statistical_comparison") {
      int pop_size, generations;
      
      std::cout << "Enter the population size: " << std::endl;
      std::cin >> pop_size;
      std::cout << "Enter the number of generations: " << std::endl;
      std::cin >> generations;
      std::cout << "Comparison is being run. This might take a while..." << std::endl;
      
      statistical_comparison(pop_size, generations);
   } else {
      WindScenario wscenario(argv[1]);
      KusiakLayoutEvaluator evaluator;
      evaluator.initialize(wscenario);	 
   
      using namespace std::placeholders;
      individual best = evolutionary_algorithm(
         evaluator,
         wscenario,
         initialization::initialization_2,
         std::bind(selection::selection_1, _1, 30),
         recombination::crossover,
         std::bind(mutation::creep, 1000.0, _1, _2),
         replacement::replacement_1,
         10);
   
      std::cout << "Best " << best.fitness << std::endl;
   }
}
