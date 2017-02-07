/* initialization.hpp
 *
 * This namespace will have all of the different implementations of the population
 * initialization of the evolutionary algorithm.
 */
#ifndef BBO_INITIALIZATION_HPP
#define BBO_INITIALIZATION_HPP

#include "API/WindFarmLayoutEvaluator.h"
#include "functions.hpp"
#include "structures.hpp"
#include "scenario.hpp"

namespace initialization {   
    std::vector<individual> init(WindFarmLayoutEvaluator &evaluator,
                                 Scenario &scenario,
                                 int pop_size);
}

#endif
