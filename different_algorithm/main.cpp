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

void start_statistics();
void start_run();

int main(int argc, const char * argv[]) {

   srand(time(NULL));
   
   bool statistics;
   std::cout << "Run a statistical comparison? (0/1)" << std::endl;
   std::cin >> statistics;
   if (statistics) {
      start_statistics();
   } else {
      start_run();
   }
}

void start_statistics() {
   std::string scenario_path;
   int pop_size, generations, iterations;
   std::cout << "Enter the test scenario path: " << std::endl;
   std::cin >> scenario_path;
   std::cout << "Enter the population size: " << std::endl;
   std::cin >> pop_size;
   std::cout << "Enter the number of generations: " << std::endl;
   std::cin >> generations;
   std::cout << "Enter the number of iterations: " << std::endl;
   std::cin >> iterations;
   std::cout << "Comparison is being run. This will take a while..." << std::endl;       
   statistical_comparison(pop_size, generations, iterations, scenario_path.c_str());
}

void start_run() {
   bool serious_mode;
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
      cevaluator->initialize(*cscenario, "XQNC1VSQ112N3I45DP56D87RYODN7Z");
      evaluator.reset(cevaluator);
   } else {
      std::string scenario_path;
      std::cout << "Enter the test scenario path: " << std::endl;
      std::cin >> scenario_path;
      wscenario.reset(new WindScenario(scenario_path.c_str()));
      scenario.reset(new Scenario(*wscenario));
      KusiakLayoutEvaluator* kevaluator = new KusiakLayoutEvaluator();
      kevaluator->initialize(*wscenario);
      evaluator.reset(kevaluator);
   }
       
   int pop_size = 0;
   int generations = 0;
   bool should_load = false;
   bool should_save = false;       
   std::cout << "Should it load from disk? (0/1)" << std::endl;
   std::cin >> should_load;
   std::cout << "Should it save data to disk? (0/1)" << std::endl;
   std::cin >> should_save;
   std::ifstream file("population.txt", std::ifstream::in);
   if (file.is_open()){
      file >> pop_size;
      file.close();
   } else {
      should_load = false;
   }
   if (!should_load){
      std::cout << "Enter the population size: " << std::endl;
      std::cin >> pop_size;
   }       
   std::cout << "Enter the number of generations: " << std::endl;
   std::cin >> generations;
 
   auto result = evolutionary_algorithm(
      *evaluator, *scenario,
      std::bind(initialization::init, _1, pop_size),
      std::bind(selection::selection_1, _1, pop_size),
      recombination::averages,
      mutation::incremental,
      std::bind(replacement::replacement_1, _1, _2, pop_size),
      generations,
      should_load, should_save);
   std::cout << "Best: " << result.first
             << ", Improvement: " << result.second << std::endl;   
}
