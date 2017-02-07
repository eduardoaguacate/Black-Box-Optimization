/* recombination.hpp
*
* This namespace will have all of the different implementations of the population
* recombination of the evolutionary algorithm.
*/
#ifndef BBO_RECOMBINATION_HPP
#define BBO_RECOMBINATION_HPP

#include "scenario.hpp"
#include "structures.hpp"

namespace recombination {
   /*
    * recombination::null
    *
    * a null recombination, aka just copying parents
    */
   std::vector<individual> none(
      const std::vector<std::vector<individual>::iterator>& parents,
      Scenario& scenario);
   
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
    * scenario - the wind scenario
    */
   std::vector<individual> crossover(
      const std::vector<std::vector<individual>::iterator>& parents,
      Scenario& scenario);
}

#endif
