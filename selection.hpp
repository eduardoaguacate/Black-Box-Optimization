/* selection.hpp
*
* This namespace has all of the different implementations of the population
* selection of the evolutionary algorithm.
*/

namespace selection{
  std::vector<std::vector<individual>::iterator> selection_1(
                                    const std::vector<individual> &individuals);
}
/* selection_1
*
* This implementation does...
* params:
*     const vector<individual> &individuals : a reference of the current
*                                             population.
*
* returns:
*     vector<vector<individual>::iterator> : contains pointers to the selected
*                                           individuals
*/
std::vector<std::vector<individual>::iterator> selection::selection_1(
                                    const std::vector<individual> &individuals){
}
