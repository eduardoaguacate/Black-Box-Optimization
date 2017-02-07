/* mutation.hpp
*
* This namespace will have all of the different implementations of the population
* mutation of the evolutionary algorithm.
*/
#ifndef BBO_MUTATION_HPP
#define BBO_MUTATION_HPP

#include "scenario.hpp"
#include "structures.hpp"

namespace mutation{
   void incremental(double range, individual& indiv, Scenario& scenario);
}

#endif
