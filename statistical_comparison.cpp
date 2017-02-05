#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <map>
#include <string>
#include <map>

#include "API/WindScenario.h"
#include "API/KusiakLayoutEvaluator.h"

#include "structures.hpp"
#include "initialization.hpp"
#include "selection.hpp"
#include "recombination.hpp"
#include "mutation.hpp"
#include "replacement.hpp"
#include "evolutionary_algorithm.hpp"

void statistical_comparison(int pop_size, 
                            int generations, 
                            int iterations,
                            const char* sc_name) {
   using namespace std::placeholders;
   // create collections of all functions of each type
   std::map<std::string, initialization_func> inits = {
      { "init_2", std::bind(initialization::initialization_2, _1, _2, pop_size) }
   };
   std::map<std::string, selection_func> selects = {
      { "tournament", std::bind(selection::selection_1, _1, pop_size) }
   };
   std::map<std::string, recombination_func> recombines = {
      { "crossover", recombination::crossover },
      { "no_recombination", recombination::none }
   };
   std::map<std::string, mutation_func> mutates = {
      { "creep(1000)", std::bind(mutation::creep, 1000.0, _1, _2) },
      { "random_reset(0.25) ", std::bind(mutation::random_reset, 0.25f, _1, _2) }
   };
   std::map<std::string, replacement_func> replaces = {
      { "age-based", replacement::age_based },
      { "fitness-based", std::bind(replacement::replacement_1, _1, _2, pop_size) }
   };

   // to keep track of the completed ea runs
   int run = 1;
   // to store the results for each combination
   std::map<std::string, std::pair<double, double>> results;
   // iterate over all combinations
   for (auto& init : inits) {
      for (auto& select : selects) {
         for (auto& recombine : recombines) {
            for (auto& mutate : mutates) {
               for (auto& replace : replaces) {
                  // create a full name for the combination
                  std::string name;
                  name.append(init.first).append(" ")
                     .append(select.first).append(" ")
                     .append(recombine.first).append(" ")
                     .append(mutate.first).append(" ")
                     .append(replace.first);
                  std::cout << "Testing " << name << std::endl;

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
                     // run the ea and store the improvement
                     double fitness = evolutionary_algorithm(
                        evaluator, scenario, init.second, select.second,
                        recombine.second, mutate.second, replace.second,
                        generations, false, false).second;
                     fitnesses.push_back(fitness);

                     std::cout << "Run " << run << ", Iteration " << j 
                               << ": " << fitness << std::endl;
                     run++;
                  }
                   
                  // compute the average
                  double average = 0.0;
                  for (auto& fitness : fitnesses) {
                     average += fitness;
                  }
                  average /= iterations;
                  // compute the standard deviation
                  double variance = 0.0;
                  for (auto& fitness : fitnesses) {
                     double delta = std::abs(average - fitness);
                     variance += delta * delta;
                  }
                  if (iterations > 1) {
                     variance /= iterations - 1;
                  }
                  double deviation = std::sqrt(variance);
                  results[name] = { average, deviation };
               }
            }
         }
      }
   }
                   
   std::cout << "=== Results in e-6 ===\n";
   const double EXPONENT = std::pow(10, 6);
   for (auto& result : results) {
       std::cout << result.first << ": " << result.second.first * EXPONENT
                 << "+-" << result.second.second * EXPONENT << '\n';
   }
   std::cout << std::flush;
}
