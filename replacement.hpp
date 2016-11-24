/* replacement.hpp
*
* This namespace has all of the different implementations of the population
* replacement of the evolutionary algorithm.
*/

namespace replacement{
  std::vector<individual> replacement_1(const std::vector<individual> &old,
                                      const std::vector<individual> &children);
}
/* replacement_1
*
* This implementation does...
* params:
*     const vector<individual> &old : a reference of the current
*                                             population.
*     const vector<individual> &children : a reference of the children created
*                                          in the current iteration
*
* returns:
*     vector<individual> : this is a new population created from both of the
*                          parameters received
*/
std::vector<individual> replacement::replacement_1(
                                    const std::vector<individual> &old,
                                    const std::vector<individual> &children){
}
