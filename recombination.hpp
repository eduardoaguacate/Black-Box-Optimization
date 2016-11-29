/* recombination.hpp
*
* This namespace will have all of the different implementations of the population
* recombination of the evolutionary algorithm.
*/

namespace recombination{
  std::vector<individual> recombination_1(
            const std::vector<std::vector<individual>::iterator> &best_individuals,
            KusiakLayoutEvaluator &evaluator);
}
/* recombination_1
*
* This implementation does...
* params:
*     const vector<individual> &individuals : a reference of the selected
                                              individuals from the population.
*     const vector<vector<individual>::iterator> &best individuals: a collection
*                                               of the population's most fitted
*                                               individuals
*
*     KusiakLayoutEvaluator &evaluator : a reference of the evaluator variable
*                                        used in the main program.
*
* returns:
*     vector<individual> : combines the selected individuals with the best
                           individuals
*/
std::vector<individual> recombination::recombination_1(
        const std::vector<std::vector<individual>::iterator> &best_individuals,
        KusiakLayoutEvaluator &evaluator){
}
