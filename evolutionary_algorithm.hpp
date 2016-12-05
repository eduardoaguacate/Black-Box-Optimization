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

// maybe move these into the function namespaces?
using initialization_func = std::function<std::vector<individual>(
                                             KusiakLayoutEvaluator&,
                                             WindScenario&)>;
using selection_func = std::function<std::vector<std::vector<individual>::iterator>(
                                        std::vector<individual>&)>;
using recombination_func = std::function<std::vector<individual>(
                                            const std::vector<std::vector<individual>::iterator>&,
                                            KusiakLayoutEvaluator&)>;
using mutation_func = std::function<void(
                                       individual&,
                                       KusiakLayoutEvaluator&)>;
using replacement_func = std::function<std::vector<individual>(
                                          const std::vector<individual>&,
                                          const std::vector<individual>&)>;
/*
 * evolutionary_algorithm
 *
 * executes an evolutionary algorithm with the specified functions
 *
 * parameters:
 * evaluator - the kusiak layout evaluator
 * wscenario - the wind scenario to solve
 * initialize - function which initializes the parameter
 * select - function which selects the parents
 * recombine - function which recombines parents
 * mutate - function which mutates children
 * replace - function which updates the population
 * generations - the number of generations until the result is obtained
 */
individual evolutionary_algorithm(KusiakLayoutEvaluator& evaluator,
                                  WindScenario& wscenario,
                                  initialization_func initialize,
                                  selection_func select,      
                                  recombination_func recombine,
                                  mutation_func mutate,
                                  replacement_func replace,
                                  int generations);

#endif
