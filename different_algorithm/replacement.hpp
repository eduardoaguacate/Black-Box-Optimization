/* replacement.hpp
 *
 * This namespace has all of the different implementations of the population
 * replacement of the evolutionary algorithm.
 */

#ifndef BBO_REPLACEMENT_HPP
#define BBO_REPLACEMENT_HPP

#include "structures.hpp"

namespace replacement {
    /* replacement_1
     *
     * This implementation does a survivor selection mechanism, in which the most
     * fitted members ar eselected, as well as some others randomly, to prevent
     * the local optimum problem
     *
     * params:
     *     const vector<individual> &old : a reference of the current
     *                                             population.
     *     const vector<individual> &children : a reference of the children created
     *                                          in the current iteration
     *     int num_population : The population number, which is the number of layouts or
     *                           individuals we are going to have per generation
     *
     * returns:
     *     vector<individual> : this is a new population created from both of the
     *                          parameters received
     */
    std::vector<individual> replacement_1(std::vector<individual> &old,
                                          std::vector<individual> &children,
                                          int num_population);

   /* replacement::age_based
    * 
    * implements age-based replacement, aka just population = children
    *
    * params:
    * old - the old population, will be discarded
    * children - the children, will make up the new population
    *
    * returns:
    * the new population
    */
   std::vector<individual> age_based(std::vector<individual>& old,
                                     std::vector<individual>& children);
}

#endif
