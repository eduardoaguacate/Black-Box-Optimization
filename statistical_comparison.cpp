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
      { "init_2", std::bind(initialization::initialization_2, _1, _2, pop_size) },
      //{ "init_1", std::bind(initialization::initialization_1, _1, _2, pop_size) }
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

   // a struct to hold the result
   struct result {
      double average;
      double variance;
      std::string name;
   };
   result best_avg{ std::numeric_limits<double>::max(), 0.0, "" };
   result best_var{ 0.0, std::numeric_limits<double>::max(), "" };
   
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
                        generations).fitness;
                     fitnesses.push_back(fitness);

                     std::cout << "Iteration " << j << ": " << fitness << std::endl;
                  }
                  
                  result r{ 0.0, 0.0, name };   
                  // compute the average
                  for (auto& fitness : fitnesses) {
                     r.average += fitness;
                  }
                  r.average /= iterations;
                  // compute the variance
                  for (auto& fitness : fitnesses) {
                     double delta = std::abs(r.average - fitness);
                     r.variance += delta * delta;
                  }
                  if (iterations > 1) {
                     r.variance /= iterations - 1;
                  }
                     
                  // update the best results
                  if (best_avg.average > r.average) {
                     best_avg = r;
                  }
                  if (best_var.variance > r.variance) {
                     best_var = r;
                  }
               }
            }
         }
      }
   }
                                
   std::cout << "=== Results ===\n";
   std::cout << "Best average: " << std::endl
             << "Name: " << best_avg.name << std::endl
             << "Average: " << best_avg.average << std::endl
             << "Variance: " << best_avg.variance << std::endl;
   std::cout << "Best (lowest) variance: " << std::endl
             << "Name: " << best_var.name << std::endl
             << "Average: " << best_var.average << std::endl
             << "Variance: " << best_var.variance << std::endl << std::endl;
}
