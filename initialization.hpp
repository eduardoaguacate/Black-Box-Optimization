/* initialization.hpp
 *
 * This namespace will have all of the different implementations of the population
 * initialization of the evolutionary algorithm.
 */
#ifndef BBO_INITIALIZATION_HPP
#define BBO_INITIALIZATION_HPP

#include "API/KusiakLayoutEvaluator.h"
#include "structures.hpp"
#include "functions.cpp"

namespace initialization {
/* initialization_1
 *
 * This implementation does...
 * params:
 *     KusiakLayoutEvaluator &evaluator : a reference of the evaluator variable
 *                                        used in the main program.
 *     WindScenario &wscenario : a reference of the wind scenario variable
 *                               used in the main program.
 *
 * returns:
 *     vector<individual> : this is a collection of all the different layouts
 *                          that are produced. In other words
 *                          this represents the population.
 */
std::vector<individual> initialization_1(KusiakLayoutEvaluator &evaluator,
                                         WindScenario &wscenario);
/* initialization_2
 *
 * This implementation initializes the population for the current generation
 * params:
 *     KusiakLayoutEvaluator &evaluator : a reference of the evaluator variable
 *                                        used in the main program.
 *     WindScenario &wscenario : a reference of the wind scenario variable
 *                               used in the main program.
 *
 * returns:
 *     vector<individual> : this is a collection of all the different layouts
 *                          that are produced. In other words
 *                          this represents the population.
 */
std::vector<individual> initialization_2(KusiakLayoutEvaluator &evaluator,
                                         WindScenario &wscenario);


/* create_individual_2
 *
 * This implementation initializes creates an individual, which is used in
 * initialization_2. It creates a layout with random coordinates, using
 * the std::uniform_real_distribution to generate them.
 *
 * params:
 *     KusiakLayoutEvaluator &evaluator : a reference of the evaluator variable
 *                                        used in the main program.
 *     WindScenario &wscenario : a reference of the wind scenario variable
 *                               used in the main program.
 *
 * returns:
 *     struct individual : this is the individual created
 */

individual create_individual_2(KusiakLayoutEvaluator &evaluator,
                               WindScenario &wscenario);

}




#endif
