/* structures.hpp
 *
 * The basic data structures that are going to be used are defined here
 */
#ifndef BBO_STRUCTURES_HPP
#define BBO_STRUCTURES_HPP

/* struct individual
 *
 * each individual (genotype) consists of 
 * the angle (phi) and the row width (rw)
 * it encodes a layout (phenotype) in which turbines are placed
 * along lines that enclose the angle phi with the y-axis
 * these lines are seperated by the row width
 */
struct individual {
  double phi;
  double rw;
  double fitness;
};

#endif
