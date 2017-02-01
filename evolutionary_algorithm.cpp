
#include "API/WindFarmLayoutEvaluator.h"
#include "evolutionary_algorithm.hpp"
#include "functions.hpp"
#include "initialization.hpp"
#include "scenario.hpp"

individual evolutionary_algorithm(WindFarmLayoutEvaluator& evaluator,
                                  Scenario& scenario,
                                  initialization_func initialize,
                                  selection_func select,
                                  recombination_func recombine,
                                  mutation_func mutate,
                                  replacement_func replace,
                                  int generations) {
   // intialization step
   std::vector<individual> population = initialize(evaluator, scenario);
   std::cout << "Initial population:" << std::endl;
   for (auto& indiv : population){
     std::cout << indiv.fitness << endl;
   }
   // this will store the maximum fittest member
   individual fittest = *population.begin();

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
         if (iter->fitness < fittest.fitness) {
            fittest = *iter;
         }
      }
      std::cout << "Fittest at generation " << g + 1 << " : " << fittest.fitness << endl;
   }

   return fittest;
}
