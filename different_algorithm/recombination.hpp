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
    * recombination::averages
    *
    * recombines parents by averaging over their attributes
    * one child is created per pair of parents
    *
    * parameters:
    *    parents - the individuals which were selected for mating
    *    scenario - the wind scenario
    *
    * postconditions:
    *    the children will NOT have been evaluated yet
    */
   std::vector<individual> averages(
      const std::vector<std::vector<individual>::iterator>& parents,
      Scenario& scenario);
}

#endif
