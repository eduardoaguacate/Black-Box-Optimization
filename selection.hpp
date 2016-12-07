/* selection.hpp
*
* This namespace has all of the different implementations of the population
* selection of the evolutionary algorithm.
*/

#include "structures.hpp"
namespace selection{

/* selection_1
 *
 * The function takes a reference to the current population
 * and the amount of requested parents as parameter
 * and returns, based on random tournament and fitness,
 * a vector of iterators to individuals within the population
 * containing the parents
 *
 *
 * parameters:  std::vector<individual> &population, int parents_amount
 * return: 	   std::vector<std::vector<individual>::iterator> parent_iterators
 *
 */
std::vector<std::vector<individual>::iterator> selection_1(
                                     std::vector<individual> &populaion,int parents_amount);
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
                                     std::vector<individual> &population,int parents_amount){
}
