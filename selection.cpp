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
std::vector<std::vector<individual>::iterator> selection::select_parents_direct(std::vector<individual> &population,int parents_amount) {
	int tournament_size = 5;
	int random_indiv = 0;
	std::vector<individual>::iterator highest_fit;
	std::vector<individual> tournament_population;
	std::vector<std::vector<individual>::iterator> parent_population;
	//choosing parent
	for (int i = 0; i < parents_amount ;i++) {
		//choosing tournament canidates
		for (int j = 0; j < tournament_size;j++) {
			random_indiv =  rand() % 30 ;
			tournament_population.push_back(population.at(random_indiv));
		}
		//get one parent with the highest fitness
		highest_fit = population.begin();
		for (auto it = population.begin(); it != population.end(); ++it) {
			if (it->fitness > highest_fit->fitness) {
				highest_fit = it;
			}
		}
		//add the highest_fitness of the tournament to the parent vector
		parent_population.push_back(highest_fit);
		tournament_population.clear();



	}
	return parent_population;
}
