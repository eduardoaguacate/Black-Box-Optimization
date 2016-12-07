#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <iterator>
#include "selection.hpp"

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
 */
std::vector<std::vector<individual>::iterator> selection::selection_1(
		 std::vector<individual> &population,int parents_amount) {


	int tournament_size = 5;
	int random_indiv = 0;
	std::vector<individual>::iterator highest_fit;
	std::vector<individual>::iterator candidate_iterator;
	std::vector<std::vector<individual>::iterator> tournament_iterators;
	std::vector<std::vector<individual>::iterator> parent_iterators;
	//choosing parents:
	for (int i = 0;i < parents_amount;i++) {
		//choosing tournament candidates
		for (int j = 0; j < tournament_size;j++) {
			random_indiv = rand() % population.size();
			candidate_iterator = population.begin() + random_indiv;
			tournament_iterators.push_back(candidate_iterator);
		}
		// get the parent with the highest fitness out of the tournament
		highest_fit = tournament_iterators.at(0);
		for (unsigned int j = 1;j < tournament_iterators.size();j++) {
			if (tournament_iterators.at(j)->fitness > (highest_fit)->fitness ) {
				highest_fit = tournament_iterators.at(j);
			}
		}
		//add the highest_fit to the parent vector
		parent_iterators.push_back(highest_fit);
		tournament_iterators.clear();
	}
	return parent_iterators;
}
