
#include "API/KusiakLayoutEvaluator.h"
#include "API/WindScenario.h"

#include "evolutionary_algorithm.hpp"

individual evolutionary_algorithm(WindScenario& wscenario,
                                  initialization_func initialize,
                                  selection_func select,      
                                  recombination_func recombine,
                                  mutation_func mutate,
                                  replacement_func replace,
                                  int generations) {
   // Create a layout evaluator
   KusiakLayoutEvaluator kle;
   kle.initialize(wscenario);
   
   // intialization step
   std::vector<individual> population = initialize(wscenario, kle);
   
   for (int g = 0; g < generations; ++g) {
      // selection step
      std::vector<std::vector<individual>::iterator> parents = select(population);
      
      // recombination, mutation step
      std::vector<individual> children = recombine(parents, kle);
      for (auto& child : children) {
         mutate(child, kle);
      }
      
      // replacement step
      population = replace(population, children);
   }
   
   // final selection, always select the fittest member
   auto fittest = population.begin();
   for (auto iter = population.begin(); iter != population.end(); ++iter) {
      if (fittest->fitness < iter->fitness) {
         fittest = iter;
      }
   }
   // TODO: if population is empty, this will crash
   // either make it a requirement that it's never empty
   // or add an exception or something
   return *fittest;
}
