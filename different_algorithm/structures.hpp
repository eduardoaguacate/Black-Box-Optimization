/*  structures.hpp
*
* The basic data structures that are going to be used are defined in this
* header file
*
*/
#ifndef BBO_STRUCTURES_HPP
#define BBO_STRUCTURES_HPP

/* struct individual
*
* Each individual is a collection of different wind turbines placed in a layout.
* Thus, an individual could be seen as a unique layout with n different turbines
* placed on it.
*
*/
struct individual{
  double phi;
  double rw;
  double fitness;
};

#endif
