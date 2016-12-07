
#include "API/KusiakLayoutEvaluator.h"
#include "API/WindScenario.h"

#include "evolutionary_algorithm.hpp"

#include "functions.hpp"

individual evolutionary_algorithm(KusiakLayoutEvaluator& evaluator,
                                  WindScenario& wscenario,
                                  initialization_func initialize,
                                  selection_func select,
                                  recombination_func recombine,
                                  mutation_func mutate,
                                  replacement_func replace,
                                  int generations) {
   // intialization step
   std::vector<individual> population = initialize(evaluator, wscenario);
   // this will store the maximum fittest member
   individual fittest = *population.begin();

   for (int g = 0; g < generations; ++g) {
      // selection step
      std::vector<std::vector<individual>::iterator> parents = select(population);
      // recombination, mutation step
      std::vector<individual> children = recombine(parents, evaluator);
      for (auto& child : children) {
         mutate(child, evaluator);
      }
      // determine the fitness of the children
      KusiakLayoutEvaluator eval;
      eval.initialize(wscenario);
      for (auto& child : children) {
         auto mat_layout = functions::individual_to_matrix<double>(child.layout);
         child.fitness = eval.evaluate(&mat_layout);
      }

      // replacement step
      population = replace(population, children);
      // update the fittest member
      for (auto iter = population.begin(); iter != population.end(); ++iter) {
         if (iter->fitness < fittest.fitness) {
            fittest = *iter;
         }
      }
   }

   return fittest;
}
