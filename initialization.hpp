/* initialization.hpp
 *
 * This namespace will have all of the different implementations of the population
 * initialization of the evolutionary algorithm.
 */
#ifndef BBO_INITIALIZATION_HPP
#define BBO_INITIALIZATION_HPP

#include "API/KusiakLayoutEvaluator.h"
#include "API/Matrix.hpp"
#include "structures.hpp"
#include "functions.hpp"

namespace initialization {
     /* initialization_1
     *
     * This function takes  the relevant layout data as parameter and produces
     * a population / vector of those turbine layouts.
     * The returned layouts are completely random based and
     * will be corrected by the "replaceviolations" function
     *
     * !! srand(time(0)); needs to be in the main function !!
     *
     * parameters: WindScenario wscenario, int pop_size
     * return: std::vector<individual> population
     *
     */
    std::vector<individual> initialization_1(KusiakLayoutEvaluator &evaluator,WindScenario &wscenario,int pop_size);

    /* initialization_2
    *
    * This implementation initializes the population for the current generation
    * params:
    *     KusiakLayoutEvaluator &evaluator : a reference of the evaluator variable
    *                                        used in the main program.
    *     WindScenario &wscenario : a reference of the wind scenario variable
    *                               used in the main program.
    *     int num_population : The population number, which is the number of layouts or
    *                           individuals we are going to have per generation
    *
    * returns:
    *     vector<individual> : this is a collection of all the different layouts
    *                          that are produced. In other words
    *                          this represents the population.
    */
    std::vector<individual> initialization_2(KusiakLayoutEvaluator &evaluator,
                                             WindScenario &wscenario,
                                             int num_population);

    /* replace_violations
     *
     * This functions takes a population reference and the layout
     * constraints as parameters, and automatically corrects
     * all turbine positions within the given population by new
     * random positions. No return value.
     *
     * !! srand(time(0)); needs to be in the main function !!
     *
     * parameters: std::vector<individual> &population
     * 			       WindScenario wscenario
     *
     * return: void
     */
    void replace_violations(std::vector<individual> &population,WindScenario &wscenario);

    /* evaluate_population
     *
     * This functions takes the population and the evaluator
     * as parameter, casts the population's individuals
     * to matrixes and evaluates them, storing the new fitnesses
     * in the population structures, no return value;
     *
     * parameters: std::vector<individual> &population, WindScenario &wscenario
     *
     * return: void
     *
    */
    void evaluate_population(KusiakLayoutEvaluator &evaluator,std::vector<individual> &population);


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
