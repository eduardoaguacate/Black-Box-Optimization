/* initialization.hpp
 *
 * This namespace will have all of the different implementations of the population
 * initialization of the evolutionary algorithm.
 */
#ifndef BBO_INITIALIZATION_HPP
#define BBO_INITIALIZATION_HPP

#include "structures.hpp"
#include "scenario.hpp"

namespace initialization {
   /*
    * initialization::init
    *
    * creates a population by creating individuals with random phi and row width
    * phi will be drawn from the uniform distribution (0, PI / 2)
    * rw will be drawn from the uniform distribution (scenario.R * 8, scenario.R * 16)
    *
    * parameters:
    *    scenario - the wind scenario the layouts will be based on
    *    pop_size - the size which the population should have
    *
    * postconditions:
    *    will return valid individuals for the scenario
    *    these individuals will NOT have been evaluated yet
    */
   std::vector<individual> init(const Scenario& scenario, int pop_size);
}

#endif
