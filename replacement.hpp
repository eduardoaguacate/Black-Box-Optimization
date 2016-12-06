/* replacement.hpp
 *
 * This namespace has all of the different implementations of the population
 * replacement of the evolutionary algorithm.
 */

#ifndef BBO_REPLACEMENT_HPP
#define BBO_REPLACEMENT_HPP

#include "structures.hpp"
#include "functions.hpp"
#include "Random.hpp"

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
 *
 * returns:
 *     vector<individual> : this is a new population created from both of the
 *                          parameters received
 */
std::vector<individual> replacement_1(std::vector<individual> &old,
                                      std::vector<individual> &children);
}

#endif
