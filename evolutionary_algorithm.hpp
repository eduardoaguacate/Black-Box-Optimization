/*
 * evolutionary_algorithm.hpp
 * 
 * contains type definitions for functions
 * and the evolutionary_algorithm interface
 */
#ifndef BBO_EVOLUTIONARY_ALGORITHM_HPP
#define BBO_EVOLUTIONARY_ALGORITHM_HPP

#include <functional>

#include "structures.hpp"

class KusiakLayoutEvaluator;
class WindScenario;

using initialization = std::function<std::vector<individual>(
                                        WindScenario&,
                                        KusiakLayoutEvaluator&)>;
using selection = std::function<std::vector<std::vector<individual>::iterator>(
                                   const std::vector<individual>&)>;
using recombination = std::function<std::vector<individual>(
                                       const std::vector<std::vector<individual>::iterator>&,
                                       KusiakLayoutEvaluator&)>;
using mutation = std::function<void(
                                  individual&,
                                  KusiakLayoutEvaluator&)>;
using replacement = std::function<std::vector<individual>(
                                     const std::vector<individual>&,
                                     const std::vector<individual>&)>;
/*
 * evolutionary_algorithm
 *
 * executes an evolutionary algorithm with the specified functions
 *
 * parameters:
 * wscenario - the wind scenario to solve
 * initialize - function which initializes the parameter
 * select - function which selects the parents
 * recombine - function which recombines parents
 * mutate - function which mutates children
 * replace - function which updates the population
 * generations - the number of generations until the result is obtained
 */
individual evolutionary_algorithm(WindScenario& wscenario,
                                  initialization initialize,
                                  selection select,      
                                  recombination recombine,
                                  mutation mutate,
                                  replacement replace,
                                  int generations);

#endif
