
#include "API/KusiakLayoutEvaluator.h"
#include "API/WindScenario.h"

#include "evolutionary_algorithm.hpp"

namespace bbo {
   individual evolutionary_algorithm(WindScenario& wscenario,
				     initialization initialize,
				     selection select,      
				     recombination recombine,
				     mutation mutate,
				     replacement replace,
				     int generations) {
      // Create a layout evaluator
      KusiakLayoutEvaluator kle;
      kle.inititalize(wscenario);
      
      // intialization step
      std::vector<individual> population = initialize(wscenario, kle);

      for (int g = 0; g < generations; ++g) {
	 // selection step
         std::vector<std::vector<individual>::iterator> parents = select(population);

	 // recombination, mutation step
         std::vector<individual> children = recombine(population, parents, kle);
         mutate(children, kle);
	 
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
}
