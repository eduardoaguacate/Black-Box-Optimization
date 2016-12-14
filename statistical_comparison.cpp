#include <cmath>
#include <iostream>
#include <limits>
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

void statistical_comparison(int pop_size, int generations) {
   using namespace std::placeholders;
   // create collections of all functions of each type
   std::unordered_map<std::string, initialization_func> inits = {
      { "init_2", initialization::initialization_2 },
      { "init_1", std::bind(initialization::initialization_1, _1, _2, pop_size) }
   };
   std::unordered_map<std::string, selection_func> selects = {
      { "tournament", std::bind(selection::selection_1, _1, pop_size) }
   };
   std::unordered_map<std::string, recombination_func> recombines = {
      { "crossover", recombination::crossover }
   };
   std::unordered_map<std::string, mutation_func> mutates = {
      { "creep(1000)", std::bind(mutation::creep, 1000.0, _1, _2) },
      { "random_reset(0.25) ", std::bind(mutation::random_reset, 0.25f, _1, _2) }
   };
   std::unordered_map<std::string, replacement_func> replaces = {
      { "fitness-based", replacement::replacement_1 }
   };

   // a struct to hold the result
   struct result {
      double average;
      double variance;
      std::string name;
   };

   // iterate over all, and determine best average and lowest variance
   result best_avg{ 0.0, 0.0, "" };
   result best_var{ 0.0, std::numeric_limits<double>::max(), "" };
   for (auto& init : inits) {
      for (auto& select : selects) {
         for (auto& recombine : recombines) {
            for (auto& mutate : mutates) {
               for (auto& replace : replaces) {
                  // some constants
                  const std::string PATH = "../Scenarios/";
                  const std::string EXT = ".xml";
                  const int NUM_SCENARIOS = 10;

                  // hold the fitness results in a vector
                  std::vector<double> fitnesses;
                  // run the algorithm on each scenario (no obstacles for now)
                  for (int i = 0; i < NUM_SCENARIOS; ++i) {
                     // create a scenario and an evaluator
                     WindScenario wscenario(PATH + "0" + std::to_string(i) + EXT);
                     KusiakLayoutEvaluator evaluator;
                     evaluator.initialize(wscenario);

                     // determine the fitness for
                     // this combination of functions and scenario
                     double fitness = evolutionary_algorithm(
                        evaluator, wscenario, init.second, select.second,
                        recombine.second, mutate.second, replace.second,
                        generations).fitness;
                     fitnesses.push_back(fitness);
                  }

                  // create a name for the combination
                  std::string name;
                  name.append(init.first).append(" ")
                     .append(select.first).append(" ")
                     .append(recombine.first).append(" ")
                     .append(mutate.first).append(" ")
                     .append(replace.first);
                  
                  result r{ 0.0, 0.0, name };
                  // compute the average
                  for (auto& fitness : fitnesses) {
                     r.average += fitness;
                  }
                  r.average /= NUM_SCENARIOS;
                  // compute the variance
                  for (auto& fitness : fitnesses) {
                     double delta = std::abs(r.average - fitness);
                     r.variance += delta * delta;
                  }
                  r.variance /= NUM_SCENARIOS - 1;

                  // update the best results
                  if (best_avg.average < r.average) {
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

   std::cout << "Best average: " << std::endl
             << "Name: " << best_avg.name << std::endl
             << "Average: " << best_avg.average << std::endl
             << "Variance: " << best_avg.variance << std::endl;
   std::cout << "Best (lowest) variance: " << std::endl
             << "Name: " << best_var.name << std::endl
             << "Average: " << best_var.average << std::endl
             << "Variance: " << best_var.variance << std::endl;
}
