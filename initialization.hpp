/* initialization.hpp
*
* This namespace will have all of the different implementations of the population
* initialization of the evolutionary algorithm.
*/

namespace initialization{
  std::vector<individual> initialization_1(KusiakLayoutEvaluator &evaluator,
                                      WindScenario &wscenario);
}

/* initialization_1
*
* This implementation does...
* params:
*     KusiakLayoutEvaluator &evaluator : a reference of the evaluator variable
*                                        used in the main program.
*     WindScenario &wscenario : a reference of the wind scenario variable
*                               used in the main program.
*
* returns:
*     vector<individual> : this is a collection of all the different layouts
*                          that are produced. In other words
*                          this represents the population.
*/
std::vector<individual> initialization::initialization_1(
                                    KusiakLayoutEvaluator &evaluator,
                                    WindScenario &wscenario){
}
