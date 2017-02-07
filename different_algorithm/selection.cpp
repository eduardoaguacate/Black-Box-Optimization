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
	int pair_size = 2;
	std::vector<individual>::iterator highest_fit;
	std::vector<individual>::iterator candidate_iterator;
	std::vector<std::vector<individual>::iterator> tournament_iterators;
	std::vector<std::vector<individual>::iterator> parent_iterators;
	//choosing parents:
	//elitist:
	highest_fit = get_best_fitness(population);
	parent_iterators.push_back(highest_fit);
	//normal
	for (int i = 1;i < parents_amount;i++) {
		
		//gurantees the worst one to be once in here
		if (i == pair_size) {
		
		highest_fit = get_worst_fitness(population);
		parent_iterators.push_back(highest_fit);
		continue;
		}
		//choosing tournament candidates
		for (int j = 0; j < tournament_size;j++) {
			random_indiv = rand() % population.size();
			candidate_iterator = population.begin() + random_indiv;
			tournament_iterators.push_back(candidate_iterator);
		}
		// get the parent with the highest fitness out of the tournament
		highest_fit = tournament_iterators.at(0);
		for (unsigned int j = 1;j < tournament_iterators.size();j++) {
			if (tournament_iterators.at(j)->fitness < (highest_fit)->fitness ) {
				highest_fit = tournament_iterators.at(j);
			}
		}
		//add the highest_fit to the parent vector
		parent_iterators.push_back(highest_fit);
		tournament_iterators.clear();
	}
	
	return parent_iterators;
}
/*
 * returns the best individual
*/
std::vector<individual>::iterator selection::get_best_fitness(std::vector<individual> &population) {
	std::vector<individual>::iterator best_fitness;
	best_fitness = population.begin();
	for(int i = 0;i < population.size();i++) {
		if(population.at(i).fitness < (best_fitness)->fitness)  {
			best_fitness = population.begin() + i; }
	}
	return best_fitness;
}
/*
 * returns the worst individual
*/
std::vector<individual>::iterator selection::get_worst_fitness(std::vector<individual> &population) {
	std::vector<individual>::iterator worst_fitness;
	worst_fitness = population.begin();
	for(int i = 0;i < population.size();i++) {
		if(population.at(i).fitness > (worst_fitness)->fitness)  {
			worst_fitness = population.begin() + i; }
	}
	return worst_fitness;	
}

