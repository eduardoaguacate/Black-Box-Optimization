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
 * a vector of individuals containing the parents
 *
 *
 * parameters: const std::vector<individual> &population, int parents_amount
 * return: 	   std::vector<individual> parents
 */
std::vector<std::vector<individual>::iterator> selection_1
	( std::vector<individual> &population,int parents_amount);
}


