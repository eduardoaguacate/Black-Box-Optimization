/*  structures.hpp
*
* The basic data structures that are going to be used are defined in this
* header file
*
*/


/* struct coordinate
*
* This data structure describes the position of a wind turbine
* in a layout
*
*/
struct coordinate{
  double x;
  double y;
};

/* struct individual
*
* Each individual is a collection of different wind turbines placed in a layout.
* Thus, an individual could be seen as a unique layout with n different turbines
* placed on it.
*
*/
struct individual{
  std::vector<coordinate> layout;
  double fitness;
};
