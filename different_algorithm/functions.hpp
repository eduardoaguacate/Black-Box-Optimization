/* initialization.hpp
 *
 * This namespace will have all of the different implementations of the population
 * initialization of the evolutionary algorithm.
 */
#ifndef BBO_FUNCTIONS_HPP
#define BBO_FUNCTIONS_HPP

#include "API/WindFarmLayoutEvaluator.h"
#include "structures.hpp"
#include "scenario.hpp"

namespace functions {
   /* individual_to_matrix
    * 
    * convert an individual (angle and row width) into a matrix of x and y coordinates
    * which can be sent to the evaluator
    *
    * parameters:
    *    scenario - the scenario the layout is based on
    *    indiv - the inidivdual
    */
   Matrix<double> individual_to_matrix(Scenario& scenario, const individual& indiv);

   /* 
    * evaluate_population
    *
    * converts individuals into matrices which can be evaluated by the API
    * then assigns to each individual the fitness value
    *
    * parameters:
    *    evaluator - the evaluator from the API
    *    scenario - a matching wind scenario
    *    population - the individuals to evaluate
    */
   void evaluate_population(WindFarmLayoutEvaluator& evaluator, Scenario& scenario,
                            std::vector<individual>& population);
   
   /* compare_fitness
    *
    * This function compares the fitnesses of two individuals
    *
    * params:
    *     a: the first individual
    *     b: the second individual to be compared
    *
    * returns:
    *     true if a.fitness is less than b.fitness, false otherwise
    */
   bool compare_fitness(const individual& a, const individual& b);
    
   /* load_population_from_file
    *
    * This function loads a population that was previously saved in a file
    *
    * params:
    *     const string file_name : where the data is stored
    *
    * returns:
    *     std::vector<individual> : the population that is stored in the file
    */
   std::vector<individual> load_population_from_file(const std::string& file_name);
    
   /* save_population_to_file
    *
    * This function saves a given population in a given file
    *
    * params:
    *     const string file_name : where the data is going to be stored
    *
    * returns:
    *     void
    */
   void save_population_to_file(const std::string& file_name, const std::vector<individual>& pop);
}

#endif
