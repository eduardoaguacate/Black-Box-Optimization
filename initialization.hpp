/* initialization.hpp
*
* This namespace will have all of the different implementations of the population
* initialization of the evolutionary algorithm.
*/

namespace initialization{
  std::vector<individual> initialization_1(KusiakLayoutEvaluator &evaluator,
                                      WindScenario &wscenario);


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
std::vector<individual> initialization_1(WindScenario wscenario,int pop_size);


/* replace_violations
 *
 * This functions takes a population reference and the layout
 * constraints as parameters, and automatically corrects
 * all turbine positions within the given population by new
 * random positions. No return value.
 * 
 * !! srand(time(0)); needs to be in the main function !!
 *
 * parameters: std::vector<individual> &population,
 * 			       WindScenario wscenario
 *
 * return: void
 */
void replace_violations(std::vector<individual> &population,WindScenario wscenario);
}
std::vector<individual> initialization::initialization_1(
                                    KusiakLayoutEvaluator &evaluator,
                                    WindScenario &wscenario){
}
