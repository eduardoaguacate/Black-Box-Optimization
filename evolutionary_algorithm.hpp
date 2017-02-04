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

class WindFarmLayoutEvaluator;
class WindScenario;
class Scenario;

// maybe move these into the function namespaces?
using initialization_func = std::function<std::vector<individual>(
                                             WindFarmLayoutEvaluator&,
                                             Scenario&)>;
using selection_func = std::function<std::vector<std::vector<individual>::iterator>(
                                        std::vector<individual>&)>;
using recombination_func = std::function<std::vector<individual>(
                                            const std::vector<std::vector<individual>::iterator>&,
                                            Scenario&)>;
using mutation_func = std::function<void(individual&, Scenario&)>;
using replacement_func = std::function<std::vector<individual>(
                                       std::vector<individual>&,
                                       std::vector<individual>&)>;
/*
 * evolutionary_algorithm
 *
 * executes an evolutionary algorithm with the specified functions
 *
 * parameters:
 * evaluator - the layout evaluator
 * scenario - the wind scenario to solve
 * initialize - function which initializes the parameter
 * select - function which selects the parents
 * recombine - function which recombines parents
 * mutate - function which mutates children
 * replace - function which updates the population
 * generations - the number of generations until the result is obtained
 * shouldLoadFile - this makes the algorithm load the data from a previous file
 * shouldSaveFile - this makes the algorithm save the data from the population at the end
 *
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
                                  bool shouldLoadFile,
                                  bool shouldSaveFile);

#endif
