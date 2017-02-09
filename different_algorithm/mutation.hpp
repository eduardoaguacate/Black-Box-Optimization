/* 
 * namespace mutation
 *
 * contains all of the mutation operators for the evolutionary algorithm
 */
#ifndef BBO_MUTATION_HPP
#define BBO_MUTATION_HPP

#include "scenario.hpp"
#include "structures.hpp"

namespace mutation {
   /*
    * mutation::incremental
    *
    * implements incremental mutation, e.g. increasing or decreasing
    * the genotype attributes phi and rw by small amounts
    *
    * parameters:
    * phi_range - the angle phi will be increased/decreased by an amount
    * drawn randomly from the uniform distribution (-phi_range * PI, phi_range * PI)
    * rw_range - the row width will be increased/decreased by an amount
    * drawn randomly from the uniform distribution (-rw_range * scenario.R, rw_range * scenario.R)
    *
    * postconditions:
    * the angle phi will be in the range [0.0, PI / 2]
    * the row width will be in the range [scenario.R * 8, scenario.R * 16]
    */
   void incremental(double phi_range, double rw_range, individual& indiv, Scenario& scenario);
}

#endif
