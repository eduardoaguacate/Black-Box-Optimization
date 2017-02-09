/*
 * evolutionary_algorithm.hpp
 *
 * contains type definitions for functions
 * and the evolutionary_algorithm interface
 */
#ifndef BBO_EVOLUTIONARY_ALGORITHM_HPP
#define BBO_EVOLUTIONARY_ALGORITHM_HPP

#include "API/WindFarmLayoutEvaluator.h"
#include "scenario.hpp"
#include "structures.hpp"

#include <functional>

// the signature of an initialization
using initialization_func = std::function<std::vector<individual>(const Scenario&)>;
// the signature of a selection
using selection_func = std::function<std::vector<std::vector<individual>::iterator>(
                                        std::vector<individual>&)>;
// the signature of a recombination
using recombination_func = std::function<std::vector<individual>(
                                            const std::vector<std::vector<individual>::iterator>&,
                                            Scenario&)>;
// the signature of a mutation
using mutation_func = std::function<void(individual&, Scenario&)>;
// the signature of a replacement
using replacement_func = std::function<std::vector<individual>(
                                       std::vector<individual>&,
                                       std::vector<individual>&)>;
/*
 * evolutionary_algorithm
 *
 * executes an evolutionary algorithm with the specified parameters
 *
 * parameters:
 *    evaluator - the layout evaluator
 *    scenario - the wind scenario to solve
 *    initialize - function which initializes the population
 *    select - function which selects the parents
 *    recombine - function which recombines parents
 *    mutate - function which mutates children
 *    replace - function which updates the population
 *    generations - the number of generations for which the algorithm is run
 *    should_load - if true, will load the initial population from disk
 *    should_save - if true, will save the population at the end
 *
 * returns:
 *    fittest, improvement - the best fitness overall and the improvement from
 *                           the initial best fitness to the final one 
 */
std::pair<double, double> evolutionary_algorithm(
                                  WindFarmLayoutEvaluator& evaluator,
                                  Scenario& scenario,
                                  initialization_func initialize,
                                  selection_func select,
                                  recombination_func recombine,
                                  mutation_func mutate,
                                  replacement_func replace,
                                  int generations,
                                  bool should_load,
                                  bool should_save);

#endif
