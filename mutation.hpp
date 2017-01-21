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
   /*
    * mutation::creep
    *
    * applies creep (incremental mutation) to one individual
    * creep steps are sampled from a cauchy distribution
    * the function tests for layout boundaries and re-enforces them
    *
    * parameters:
    * range - the distribution will be (-range, range)
    * individual - the individual to mutate
    * kle - the evaluator
    */
   void creep(double range, individual& indiv, Scenario& scenario);
   
   /*
    * mutation::random_reset
    *
    * applies a mutation which simply resets a random number of coordinates
    * each x and y coordinate has a chance to be reset independently
    * reset coordinates are drawn uniformly from 0 to the layout boundaries
    *
    * parameters:
    * chance - probability that a coordinate is reset
    * individual - the individual to mutate
    * kle - the evaluator
    */
   void random_reset(float chance, individual& indiv, Scenario& scenario);
}

#endif
