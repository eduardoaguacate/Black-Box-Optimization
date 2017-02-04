
#include "API/WindFarmLayoutEvaluator.h"
#include "evolutionary_algorithm.hpp"
#include "functions.hpp"
#include "initialization.hpp"
#include "scenario.hpp"

std::pair<double, double> evolutionary_algorithm(
                                  WindFarmLayoutEvaluator& evaluator,
                                  Scenario& scenario,
                                  initialization_func initialize,
                                  selection_func select,
                                  recombination_func recombine,
                                  mutation_func mutate,
                                  replacement_func replace,
                                  int generations,
                                  bool shouldLoadFile,
                                  bool shouldSaveFile) {
   // intialization step
   string file_name = "population.txt";
   std::vector<individual> population = shouldLoadFile ? functions::load_population_from_file(file_name) : initialize(evaluator, scenario);
   std::cout << "Initial population:" << std::endl;
   for (auto& indiv : population){
     std::cout << indiv.fitness << std::endl;
   }
   
   // the best (lowest) fittness
   double fittest = population.begin()->fitness;
   // the average fitness of the initial population
   double avg_fitness = 0.0;
   for (auto& indiv : population) {
      avg_fitness += indiv.fitness;
      if (fittest > indiv.fitness) {
         fittest = indiv.fitness;
      }
   }
   avg_fitness /= population.size();
   
   std::cout << "Initial fittest: " << fittest << std::endl;
   std::cout << "Initial average: " << avg_fitness << std::endl;
   
   for (int g = 0; g < generations; ++g) {
      // selection step
      std::vector<std::vector<individual>::iterator> parents = select(population);
      
      // recombination, mutation step
      std::vector<individual> children = recombine(parents, scenario);
      for (auto& child : children) {
	     mutate(child, scenario);
      }

      initialization::replace_violations(children, scenario);
      
      // determine the fitness of the children
      for (auto& child : children) {
         functions::remove_illegal_coordinates(child, scenario);
         auto mat_layout = functions::individual_to_matrix<double>(child.layout);
         child.fitness = evaluator.evaluate(&mat_layout);
      }

      // replacement step
      population = replace(population, children);
      // update the fittest member
      for (auto iter = population.begin(); iter != population.end(); ++iter) {
         if (fittest > iter->fitness) {
            fittest = iter->fitness;
         }
      }
      std::cout << "Fittest at generation " << g + 1 << " : " << fittest << endl;
   }
    if (shouldSaveFile){
        functions::save_population_to_file(file_name, population);
    }

   return{ fittest, avg_fitness - fittest };
}
