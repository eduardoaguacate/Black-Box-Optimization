/* initialization.hpp
 *
 * This namespace will have all of the different implementations of the population
 * initialization of the evolutionary algorithm.
 */
#ifndef BBO_FUNCTIONS_HPP
#define BBO_FUNCTIONS_HPP

#include "API/Matrix.hpp"
#include "structures.hpp"
#include "API/KusiakLayoutEvaluator.h"

namespace functions {
    /* turbine_collides
     *
     * This method checks whether a given coordinate is already used
     * params:
     *      double x : the coordinate x of the turbine
     *      double y : the coordinate y of the turbine
     *      KusiakLayoutEvaluator evaluator : 
                                            the KusiakLayoutEvaluator of the api
     *      std::vector<coordinate> &layout: the layout with all the coordinates
     *
     * returns:
     *      bool : true if it collides, false otherwise
     */
    bool turbine_collides(double x, double y, KusiakLayoutEvaluator &evaluator,
                          std::vector<coordinate> &layout);

    /*
     * remove_illegal_coordinates
     * 
     * removes coordinates which are placed on an obstacle
     * does nothing if there are no obstacles in the scenario
     * in practice, this should be balanced with a mechanism to increase the
     * number of turbines through mutation or recombination
     * 
     * params: individual and wind scenario
     */
    void remove_illegal_coordinates(individual& indiv, WindScenario& wscenario);

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
}

template<typename T>
Matrix<T> functions::individual_to_matrix(std::vector<coordinate> &vector){
        int i = 0;
        Matrix<T> matrix(vector.size(),2);
        for (auto it = vector.begin(); it < vector.end(); ++it, ++i) {
                matrix.set(i,0,it->x);
                matrix.set(i,1,it->y);
        }
        return matrix;
}

#endif
