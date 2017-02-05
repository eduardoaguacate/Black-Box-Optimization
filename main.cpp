/*  main.cpp
 *
 *   This is the class in which the evolutionary algorithm is going to be run.
 *   Version: 1.0.0
 */

//STL libraries
#include <memory>
#include <iostream>
#include <string>

//API libraries
#include "API/CompetitionScenario.h"
#include "API/WindScenario.h"
#include "API/KusiakLayoutEvaluator.h"
#include "API/CompetitionEvaluator.h"

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
#include <fstream>

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
       
       statistical_comparison(pop_size, generations, iterations, argv[2]);
   } else {
       bool serious_mode = false;
       std::cout << "Run against the server? (0/1)" << std::endl;
       std::cin >> serious_mode;
       
       std::unique_ptr<WindFarmLayoutEvaluator> evaluator;
       std::unique_ptr<CompetitionScenario> cscenario;
       std::unique_ptr<WindScenario> wscenario;
       std::unique_ptr<Scenario> scenario;
       if (serious_mode) {
          int sc_number;
          std::cout << "Scenario number? (1 to 5)" << std::endl;
          std::cin >> sc_number;
          cscenario.reset(new CompetitionScenario(sc_number));
          scenario.reset(new Scenario(*cscenario));
          CompetitionEvaluator* cevaluator = new CompetitionEvaluator();
          cevaluator->initialize(*cscenario, "RFCU5KIPRGAZUAQJH802YJDXNJSWGC");
          evaluator.reset(cevaluator);
       } else {
          wscenario.reset(new WindScenario(argv[1]));
          scenario.reset(new Scenario(*wscenario));
          KusiakLayoutEvaluator* kevaluator = new KusiakLayoutEvaluator();
          kevaluator->initialize(*wscenario);
          evaluator.reset(kevaluator);
       }
       
       int pop_size = 0;
       int generations = 0;
       bool shouldLoadFile = false;
       bool shouldSaveFile = false;
       
       std::cout << "Should it load from disk? (0/1)" << std::endl;
       std::cin >> shouldLoadFile;
       std::cout << "Should it save data to disk? (0/1)" << std::endl;
       std::cin >> shouldSaveFile;
       std::ifstream file("population.txt", std::ifstream::in);
       if (file.is_open()){
           file >> pop_size;
           file.close();
       }
       else{
           shouldLoadFile = false;
       }
       if (!shouldLoadFile){
           std::cout << "Enter the population size: " << std::endl;
           std::cin >> pop_size;
       }
       std::cout << "Enter the number of generations: " << std::endl;
       std::cin >> generations;
       double fitness = evolutionary_algorithm(
          *evaluator,
          *scenario,
          std::bind(initialization::initialization_2, _1,_2,pop_size),
          std::bind(selection::selection_1, _1, pop_size),
          recombination::crossover,
          std::bind(mutation::random_reset, 0.1, _1, _2),
          std::bind(replacement::replacement_1,_1,_2, pop_size),
          generations,
          shouldLoadFile,
          shouldSaveFile
          ).first;
       std::cout << "Best " << fitness << std::endl;
   }
}
