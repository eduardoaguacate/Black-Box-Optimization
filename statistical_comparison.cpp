#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <map>
#include <string>
#include <unordered_map>

#include "API/WindScenario.h"
#include "API/KusiakLayoutEvaluator.h"

#include "structures.hpp"
#include "initialization.hpp"
#include "selection.hpp"
#include "recombination.hpp"
#include "mutation.hpp"
#include "replacement.hpp"
#include "evolutionary_algorithm.hpp"

void statistical_comparison(int pop_size, int generations, int iterations,
                            const char* sc_name) {
   using namespace std::placeholders;
   // create collections of all functions of each type
   std::unordered_map<std::string, initialization_func> inits = {
      { "init_2", std::bind(initialization::initialization_2, _1, _2, pop_size) }
   };
   std::unordered_map<std::string, selection_func> selects = {
      { "tournament", std::bind(selection::selection_1, _1, pop_size) }
   };
   std::unordered_map<std::string, recombination_func> recombines = {
      { "no_recombination", recombination::none }, 
      { "crossover", recombination::crossover }
   };
   std::unordered_map<std::string, mutation_func> mutates = {
      { "creep(1000)", std::bind(mutation::creep, 1000.0, _1, _2) },
      { "random_reset(0.25) ", std::bind(mutation::random_reset, 0.25f, _1, _2) }
   };
   std::unordered_map<std::string, replacement_func> replaces = {
      { "fitness-based", std::bind(replacement::replacement_1, _1, _2, pop_size) },
      { "age-based", replacement::age_based }
   };

   std::vector<std::pair<std::string, double>> averages;
   std::vector<std::pair<std::string, double>> variances;
   
   // iterate over all, and determine best average and lowest variance
   for (auto& init : inits) {
      for (auto& select : selects) {
         for (auto& recombine : recombines) {
            for (auto& mutate : mutates) {
               for (auto& replace : replaces) {
                  // create a name for the combination
                  std::string name;
                  name.append(init.first).append(" ")
                     .append(select.first).append(" ")
                     .append(recombine.first).append(" ")
                     .append(mutate.first).append(" ")
                     .append(replace.first);

                  std::cout << "Testing: " << name << std::endl;

                  // create a scenario
                  WindScenario wscenario(sc_name);
                  Scenario scenario(wscenario);

                  // run the algorithm on the scenario
                  // hold the fitness results in a vector
                  std::vector<double> fitnesses;
                  // determine the average fitness for
                  // this combination of functions and scenario
                  for (int j = 0; j < iterations; ++j) {
                     // create an evaluator for this run
                     KusiakLayoutEvaluator evaluator;
                     evaluator.initialize(wscenario);
                     double fitness = evolutionary_algorithm(
                        evaluator, scenario, init.second, select.second,
                        recombine.second, mutate.second, replace.second,
                        generations).second;
                     fitnesses.push_back(fitness);

                     std::cout << "Iteration " << j << ": " << fitness << std::endl;
                  }
                   
                  // compute the average
                  double average = 0.0;
                  for (auto& fitness : fitnesses) {
                     average += fitness;
                  }
                  average /= iterations;
                  // compute the variance
                  double variance = 0.0;
                  for (auto& fitness : fitnesses) {
                     double delta = std::abs(average - fitness);
                     variance += delta * delta;
                  }
                  if (iterations > 1) {
                     variance /= iterations - 1;
                  }
                  averages.push_back({ name, average });
                  variances.push_back({ name, variance });
               }
            }
         }
      }
   }
   std::sort(averages.begin(), averages.end(), 
       [](const std::pair<std::string, double>& a, 
          const std::pair<std::string, double>& b){
              return a.second > b.second;
          });
   std::sort(variances.begin(), variances.end(), 
       [](const std::pair<std::string, double>& a, 
          const std::pair<std::string, double>& b){
              return a.second < b.second;
          });
                   
   std::cout << "=== Results ===\n";
   std::cout << "= Averages =\n";
   for (auto& avg : averages) {
       std::cout << avg.first << ": " << avg.second << '\n';
   }
   std::cout << "= Variances =\n";
   for (auto& var : variances) {
       std::cout << var.first << ": " << var.second << '\n';
   }
   std::cout << std::flush;
}
