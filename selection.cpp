#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <iterator>
#include "selection.hpp"

/* select_parents_direct
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
std::vector<individual> selection::select_parents_direct(const std::vector<individual> &population,int parents_amount) {
	int tournament_size = 5;
	int random_indiv = 0;
	individual highest_fit;
	std::vector<individual> tournament_population;
	std::vector<individual> parent_population;
	//choosing parent
	for (int i = 0; i < parents_amount ;i++) {
		//choosing tournament canidates
		for (int j = 0; j < tournament_size;j++) {
			random_indiv =  rand() % 30 ;
			tournament_population.push_back(population.at(random_indiv));
		}
		//get one parent with the highest fitness
		highest_fit = tournament_population.at(0);
		for (int j = 1; j < tournament_size; j++) {
			if (tournament_population.at(j).fitness > highest_fit.fitness) {
				highest_fit = tournament_population.at(j);
			}
		}
		//add the highest_fitness of the tournament to the parent vector
		parent_population.push_back(highest_fit);
		tournament_population.clear();



	}
	return parent_population;
}
