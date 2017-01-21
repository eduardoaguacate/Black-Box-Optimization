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
#include "scenario.hpp"
#include <time.h>
#include <stdlib.h>

using namespace std::placeholders;
int main(int argc, const char * argv[]) {

   srand(time(NULL));

   std::string arg1 = argv[1];
   if (arg1 == "statistical_comparison") {
       int pop_size, generations, iterations;
       std::cout << "Enter the population size: " << std::endl;
       std::cin >> pop_size;
       std::cout << "Enter the number of generations: " << std::endl;
       std::cin >> generations;
       std::cout << "Enter the number of iterations: " << std::endl;
       std::cin >> iterations;
       std::cout << "Comparison is being run. This will take a while..." << std::endl;
       
       statistical_comparison(pop_size, generations, iterations);
   } else {
       WindScenario wscenario(argv[1]);
       KusiakLayoutEvaluator evaluator;
       evaluator.initialize(wscenario);
       Scenario scenario(wscenario);
       std::cout << wscenario.nturbines << " : " << scenario.max_turbines << std::endl;
       int pop_size;
       int generations;
       int function;
       std::cout << "Enter the population size: " << std::endl;
       std::cin >> pop_size;
       std::cout << "Enter the number of generations: " << std::endl;
       std::cin >> generations;
       std::cout << "Enter which initialization function you'll want to use (1/2): " << std::endl;
       std::cin >> function;
       individual best = evolutionary_algorithm(
          evaluator,
          scenario,
          std::bind(function == 1 ? initialization::initialization_1 :
                    initialization::initialization_2, _1,_2,pop_size),
          std::bind(selection::selection_1, _1, pop_size),
          recombination::crossover,
          std::bind(mutation::random_reset, 0.1, _1, _2),
          std::bind(replacement::replacement_1,_1,_2, pop_size),
          generations
          );
       std::cout << "Best " << best.fitness << std::endl;
   }
}
