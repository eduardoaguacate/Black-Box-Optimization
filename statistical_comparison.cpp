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

void statistical_comparison(int pop_size, int generations, int iterations) {
   using namespace std::placeholders;
   // create collections of all functions of each type
   std::unordered_map<std::string, initialization_func> inits = {
       { "init_2", std::bind(initialization::initialization_2,_1,_2, pop_size) },
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
      { "fitness-based", std::bind(replacement::replacement_1,_1,_2, pop_size) }
   };

   // a struct to hold the result
   struct result {
      double average;
      double variance;
      std::string name;
   };

   // the number of scenarios to evaluate
   const int NUM_SCENARIOS = 10;
   std::vector<result> best_avg(NUM_SCENARIOS, { 0.0, std::numeric_limits<double>::max(), "" });
   std::vector<result> best_var(NUM_SCENARIOS, { 0.0, std::numeric_limits<double>::max(), "" });
   
   // iterate over all, and determine best average and lowest variance
   for (auto& init : inits) {
      for (auto& select : selects) {
         for (auto& recombine : recombines) {
            for (auto& mutate : mutates) {
               for (auto& replace : replaces) {
                  // some constants
                  const std::string PATH = "../Scenarios/";
                  const std::string EXT = ".xml";
                  
                  // create a name for the combination
                  std::string name;
                  name.append(init.first).append(" ")
                     .append(select.first).append(" ")
                     .append(recombine.first).append(" ")
                     .append(mutate.first).append(" ")
                     .append(replace.first);

                  // run the algorithm on each scenario (no obstacles for now)
                  for (int sc_id = 0; sc_id < NUM_SCENARIOS; ++sc_id) {
                     // create a scenario and an evaluator
                     WindScenario wscenario(PATH + "0" + std::to_string(sc_id) + EXT);
                     KusiakLayoutEvaluator evaluator;
                     evaluator.initialize(wscenario);

                     // hold the fitness results in a vector
                     std::vector<double> fitnesses;
                     // determine the average fitness for
                     // this combination of functions and scenario
                     for (int j = 0; j < iterations; ++j) {
                        double fitness = evolutionary_algorithm(
                           evaluator, wscenario, init.second, select.second,
                           recombine.second, mutate.second, replace.second,
                           generations).fitness;
                        fitnesses.push_back(fitness);
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
                     r.variance /= iterations - 1;
                     
                     // update the best results
                     if (best_avg[sc_id].average > r.average) {
                        best_avg[sc_id] = r;
                     }
                     if (best_var[sc_id].variance > r.variance) {
                        best_var[sc_id] = r;
                     }
                  }
               }
            }
         }
      }
   }
                                
   for (int sc_id = 0; sc_id < NUM_SCENARIOS; ++sc_id) {
      std::cout << "=== Results for scenario " << sc_id << "===" << std::endl;
      std::cout << "Best average: " << std::endl
                << "Name: " << best_avg[sc_id].name << std::endl
                << "Average: " << best_avg[sc_id].average << std::endl
                << "Variance: " << best_avg[sc_id].variance << std::endl;
      std::cout << "Best (lowest) variance: " << std::endl
                << "Name: " << best_var[sc_id].name << std::endl
                << "Average: " << best_var[sc_id].average << std::endl
                << "Variance: " << best_var[sc_id].variance << std::endl << std::endl;
   }

   std::cout << "=== Overall results ===" << std::endl;
   // count how many times each combination occurs
   std::unordered_map<std::string, int> best_avg_counts;
   for (auto& ba_iter : best_avg) {
      auto bac_iter = best_avg_counts.find(ba_iter.name);
      if (bac_iter == best_avg_counts.end()) {
         best_avg_counts.emplace(ba_iter.name, 1);
      } else {
         bac_iter->second++;
      }
   }
   std::unordered_map<std::string, int> best_var_counts;
   for (auto& bv_iter : best_var) {
      auto bav_iter = best_var_counts.find(bv_iter.name);
      if (bav_iter == best_var_counts.end()) {
         best_var_counts.emplace(bv_iter.name, 1);
      } else {
         bav_iter->second++;
      }
   }

   // create a mapping from counts to names
   std::multimap<int, std::string> best_avg_order;
   for (auto& bac_iter : best_avg_counts) {
      best_avg_order.emplace(bac_iter.second, bac_iter.first);
   }
   std::multimap<int, std::string> best_var_order;
   for (auto& bav_iter : best_var_counts) {
      best_var_order.emplace(bav_iter.second, bav_iter.first);
   }

   std::cout << "Most often best average: " << std::endl;
   int avg_rank = 1;
   int last_avg_count = 0;
   auto bao_it = best_avg_order.rbegin();
   auto bao_end = best_avg_order.rend();
   for (; bao_it != bao_end; ++bao_it) {
      std::cout << "Rank " << avg_rank << ": "
                << bao_it->second << std::endl;
      if (bao_it->first != last_avg_count) {
         last_avg_count = bao_it->first;
         avg_rank++;
      }
   }
   std::cout << "Most often best variance: " << std::endl;
   int var_rank = 1;
   int last_var_count = 0;
   auto bvo_it = best_var_order.rbegin();
   auto bvo_end = best_var_order.rend();
   for (; bvo_it != bvo_end; ++bvo_it) {
      std::cout << "Rank " << var_rank << ": "
                << bvo_it->second << std::endl;
      if (bvo_it->first != last_var_count) {
         last_var_count = bvo_it->first;
         var_rank++;
      }
   }
}
