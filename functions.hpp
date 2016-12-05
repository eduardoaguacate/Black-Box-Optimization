/* initialization.hpp
 *
 * This namespace will have all of the different implementations of the population
 * initialization of the evolutionary algorithm.
 */
#ifndef BBO_FUNCTIONS_HPP
#define BBO_FUNCTIONS_HPP

#include "API/Matrix.hpp"
#include "structures.hpp"

namespace functions {
   /* turbine_collides
    *
    * This method checks whether a given coordinate is already used
    * params:
    *      int x : the coordinate x of the turbine
    *      int y : the coordinate y of the turbine
    *      std::vector<coordinate> &layout: the layout with all the coordinates
    *
    * returns:
    *      bool : true if it collides, false otherwise
    */
   bool turbine_collides(double x, double y, double min_distance,
                         std::vector<coordinate> &layout);

   /* vector_to_matrix
    *
    * This method makes a matrix<T> out of a vector<coordinate>
    * params:
    *      vector<coordinate> vector: the vector to be made into a matrix
    *
    * returns:
    *      Matrix<T> : the matrix made out of the vector<coordinate>
    */
   template<typename T>
   Matrix<T> individual_to_matrix(std::vector<coordinate> &vector);
}

#endif
