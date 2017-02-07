/* initialization.hpp
 *
 * This namespace will have all of the different implementations of the population
 * initialization of the evolutionary algorithm.
 */
#ifndef BBO_FUNCTIONS_HPP
#define BBO_FUNCTIONS_HPP

#include "API/Matrix.hpp"
#include "structures.hpp"
#include "scenario.hpp"

namespace functions {
   /* individual_to_matrix
    * 
    * convert an individual (angle and row width) into a matrix of x and y coordinates
    * which can be sent to the evaluator
    *
    */
   Matrix<double> individual_to_matrix(Scenario& scenario, double phi, double rw);
   
   /* compare_fitness
    *
    * This function compares the fitnesses of two individuals
    *
    * params:
    *     const individual &indiv: the first individual
    *     const individual &indiv2: the second individual to be compared
    *
    * returns:
    *     bool : true if indiv->fitness is less than indiv2->fitness2
    *            false otherwise
    */
   bool compare_fitness(const individual &indiv,const individual &indiv2);
    
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
   std::vector<individual> load_population_from_file(const string file_name);
    
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
   void save_population_to_file(const string file_name,
                                vector<individual> &pop);
}

#endif
