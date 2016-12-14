#ifndef BBO_STATISTICAL_COMPARISON_HPP
#define BBO_STATISTICAL_COMPARISON_HPP

/*
 * statistical_comparison
 *
 * compares combinations of different functions
 * for each scenario prints
 * the combination with the best average
 * and the one with the lowest variance
 *
 * parameters:
 * pop_size - population size
 * generations - generations
 * iterations - the number of times each scenario is tried
 */
void statistical_comparison(int pop_size, int generations, int iterations);

#endif
