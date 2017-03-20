#include <algorithm>
#include <cmath>
#include <iostream>
#include <iomanip>
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
      { "init", std::bind(initialization::init, _1, pop_size) }
   };
   std::map<std::string, selection_func> selects = {
      { "tournament", std::bind(selection::selection_1, _1, pop_size) }
   };
   std::map<std::string, recombination_func> recombines = {
      { "averages", recombination::averages }
   };
   std::map<std::string, mutation_func> mutates = {
      { "incremental(1/16, 1/4)", std::bind(mutation::incremental, _1, _2, _3) }
   };
   std::map<std::string, replacement_func> replaces = {
      { "fitness-based", std::bind(replacement::replacement_1, _1, _2, pop_size) }
   };

   // to keep track of the completed ea runs
   int run = 1;
   // to store the results for each combination
   struct Statistic {
      std::vector<std::pair<double, double>> results;
      double fitness_avg; // fitness mean
      double fitness_dev; // fitness standard deviation
      double improvement_avg; // improvement mean
      double improvement_dev; // improvement standard deviation
   };
   std::map<std::string, Statistic> statistics;
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
                  std::vector<std::pair<double, double>> results;
                  // determine the average fitness for
                  // this combination of functions and scenario
                  for (int j = 0; j < iterations; ++j) {
                     // create an evaluator for this run
                     KusiakLayoutEvaluator evaluator;
                     evaluator.initialize(wscenario);
                     // run the ea and store the improvement
                     auto result = evolutionary_algorithm(
                        evaluator, scenario, init.second, select.second,
                        recombine.second, mutate.second, replace.second,
                        generations, false, false);
                     results.push_back(result);

                     std::cout << "Run " << run << ", Iteration " << j + 1
                               << ": " << result.first 
                               << ", " << result.second << std::endl;
                     run++;
                  }
                   
                  // compute the average
                  double fitness_avg = 0.0;
                  double improvement_avg = 0.0;
                  for (auto& result : results) {
                     fitness_avg += result.first;
                     improvement_avg += result.second;
                  }
                  fitness_avg /= iterations;
                  improvement_avg /= iterations;
                  // compute the standard deviation
                  double fitness_var = 0.0;
                  double improvement_var = 0.0;
                  for (auto& result : results) {
                     fitness_var += std::abs(std::pow(fitness_avg - result.first, 2));
                     improvement_var += std::abs(std::pow(improvement_avg - result.second, 2));
                  }
                  if (iterations > 1) {
                     fitness_var /= iterations - 1;
                     improvement_var /= iterations - 1;
                  }
                  double fitness_dev = std::sqrt(fitness_var);
                  double improvement_dev = std::sqrt(improvement_var);
                  statistics[name] = { 
                     results, 
                     fitness_avg, fitness_dev, improvement_avg, improvement_dev 
                  };
               }
            }
         }
      }
   }
                   
   std::cout << std::fixed << std::setprecision(10);
   std::cout << "=== Results in e-6 ===\n";
   const double EXPONENT = std::pow(10, 6);
   for (auto& statistic : statistics) {
      std::cout << statistic.first << '\n';
      for (auto& result : statistic.second.results) {
         std::cout << result.first * EXPONENT << ' ' 
                   << result.second * EXPONENT << '\n';
      }
      std::cout << "Best: " 
                << statistic.second.fitness_avg * EXPONENT 
                << "+-" << statistic.second.fitness_dev * EXPONENT 
                << ", Improvement: "
                << statistic.second.improvement_avg * EXPONENT
                << "+-" << statistic.second.improvement_dev * EXPONENT 
                << '\n';
   }
   std::cout << std::flush;
}
