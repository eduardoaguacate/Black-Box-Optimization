
#include "evolutionary_algorithm.hpp"
#include "functions.hpp"
#include "initialization.hpp"
#include "scenario.hpp"
#include <algorithm>

std::pair<double, double> evolutionary_algorithm(
                                  WindFarmLayoutEvaluator& evaluator,
                                  Scenario& scenario,
                                  initialization_func initialize,
                                  selection_func select,
                                  recombination_func recombine,
                                  mutation_func mutate,
                                  replacement_func replace,
                                  int generations,
                                  bool should_load,
                                  bool should_save) {
   // intialization step
   std::string file_name = "population.txt";
   auto population = should_load ?
      functions::load_population_from_file(file_name) : initialize(scenario);
   functions::evaluate_population(evaluator, scenario, population);
   // return if pop_size is 0 or loading failed
   if (population.empty())
      return{ 0.0, 0.0 };
   
   // determine the initial best (lowest) fittness
   double fittest = population.begin()->fitness;
   for (auto& indiv : population) {
      if (fittest > indiv.fitness) {
         fittest = indiv.fitness;
      }
   }
   double initial_fittest = fittest;
   //std::cout << "Initial fittest: " << fittest << std::endl;

   // run the algorithm for the specified number of generations
   for (int g = 0; g < generations; ++g) {
      // output the population
      std::sort(population.begin(), population.end(), functions::compare_fitness);
      std::cout << "Population after generation " << g << ":\n";
      for (auto& indiv : population) {
         std::cout << "fitness: " << indiv.fitness
                   << ", phi: " << indiv.phi
                   << ", rw: " << indiv.rw << std::endl;
      }
      
      // selection step
      auto parents = select(population);
      
      // recombination, mutation step
      auto children = recombine(parents, scenario);
      std::sort(children.begin(), children.end(), functions::compare_fitness);
      for (int i = 0; i < children.size(); ++i) {
         mutate(children[i], children.size() - i + 1, scenario);
      } 
      // determine the fitness of the children
      functions::evaluate_population(evaluator, scenario, children);

      // replacement step
      population = replace(population, children);
      // update the fittest member
      for (auto& indiv : population) {
         if (fittest > indiv.fitness) {
            fittest = indiv.fitness;
         }
      }
      // output the new fittest member
      //std::cout << "Fittest at generation " << g + 1 << " : " << fittest << std::endl;
      
      /*double gaverage = 0.0;
      auto gfittest = population.begin();
      auto gworst = population.begin();
      for (auto it = population.begin(); it != population.end(); ++it) {
         if (gfittest->fitness > it->fitness) 
            gfittest = it;
         if (gworst->fitness < it->fitness) 
            gworst = it;
         gaverage += it->fitness;
      }
      std::cout << "Generation " << g + 1 << std::endl;
      std::cout << gaverage / population.size() << std::endl;
      std::cout << gfittest->fitness << ", " << gfittest->phi << ", " << gfittest->rw << std::endl;
      std::cout << gworst->fitness << ", " << gworst->phi << ", " << gworst->rw << std::endl;*/
   }
   //std::cout << "Evaluations used: " << evaluator.getNumberOfEvaluation() << std::endl;

   if (should_save) {
      functions::save_population_to_file(file_name, population);
   }

   // return the fittest member and the improvement from initial fittest to now
   return{ fittest, initial_fittest - fittest };
}
