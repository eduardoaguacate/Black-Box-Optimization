/* recombination.hpp
*
* This namespace will have all of the different implementations of the population
* recombination of the evolutionary algorithm.
*/
#ifndef BBO_RECOMBINATION_HPP
#define BBO_RECOMBINATION_HPP

#include "API/KusiakLayoutEvaluator.h"

#include "structures.hpp"

namespace recombination {
   /*
    * recombination::crossover
    *
    * recombines parents by crossover
    * first randomly determines a cutoff from [0, size]
    * the childs turbines will then be copied from the parents,
    * turbines with indices [0, cutoff] from parent a, [cutoff, size] from b
    *
    * parameters:
    * parents - the individuals which were selected for mating
    * kle - the kusiak layout evaluator
    */
   std::vector<individual> crossover(
      const std::vector<std::vector<individual>::iterator>& parents,
      KusiakLayoutEvaluator& kle);
}

#endif
