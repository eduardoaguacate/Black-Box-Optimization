
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
      std::cout << "Parents  " << parents.size() << std::endl;
      // recombination, mutation step
      std::vector<individual> children = recombine(parents, evaluator);
      for (auto& child : children) {
         mutate(child, evaluator);
      }
      std::cout << "Children 1 " << children.size() << std::endl;
      // determine the fitness of the children
      for (auto& child : children) {
        std::cout << "evaluating1 " << child.layout.size() << std::endl;
         auto mat_layout = functions::individual_to_matrix<double>(child.layout);
         std::cout << "evaluating2" << std::endl;
         child.fitness = evaluator.evaluate_2014(&mat_layout);
      }

      // replacement step
      population = replace(population, children);
      std::cout << "Children 2"  <<population.size() << std::endl;
      // update the fittest member
      for (auto iter = population.begin(); iter != population.end(); ++iter) {
         if (fittest.fitness < iter->fitness) {
            fittest = *iter;
         }
      }
   }

   return fittest;
}
