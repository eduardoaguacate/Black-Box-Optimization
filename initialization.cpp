
#include "initialization.hpp"
#include <vector>
#include "structures.hpp"
#include <stdlib.h>
#include <time.h>
#include <iostream>

/* initialization_1
 *
 * This function takes the WindScenario (and its ayout data) and
 * the population size as parameter and creates
 * a population / vector of those turbine layouts.
 * The returned layouts are completely random based and
 * will be corrected by the "replace_violations" function
 *
 * !! srand(time(0)); needs to be in the main function !!
 * !! currently no evaluation of the population implemented !!
 * 
 * parameters: WindScenario wscenario, int pop_size
 * return: std::vector<individual> population
 *
 */
std::vector<individual> initialization::initialization_1(WindScenario wscenario,int pop_size) {

	std::vector<individual> population;
	individual indiv;
	coordinate coord;


	for (int j = 0; j < pop_size;j++){
		//initiate layout (coordinates)
		for (int i = 0;i < turbines; i++) {
			//creates coordinates and puts them into the individual
			coord.x = wscenario.width * (double) rand() / (double) RAND_MAX;
			coord.y = wscenario.height * (double) rand() / (double) RAND_MAX;
			indiv.layout.push_back(coord);
		}

		population.push_back(indiv);
		indiv.layout.clear();
	}
	initialization::replace_violations(population,wscenario);
	return population;

}

/* replace_violations
 *
 * This functions takes a population reference and the layout
 * constraints from the WindScenario as parameters, 
 * and automatically corrects
 * all turbine positions within the given population by new
 * random positions. No return value.
 *
 * !! srand(time(0)); needs to be in the main function !!
 *
 * parameters: std::vector<individual> &population,
 * 			       WindScenario wscenario
 *
 * return: void
 */
void initialization::replace_violations(std::vector<individual> &population,WindScenario wscenario) {


	double radius = wscenario.R * 8.001; //distance must be radius*8
	//population.at(i).layout.at(j).x
	//thirst loop to pick an individual, second to pick a coordinate to be checked
	//third loop to compare the chosen coordinate with all other coordinates
	//within the individuals layout
	for (int i = 0;i < population.size(); i++) {
		for (int j = 0; j < population.at(i).layout.size();j++){
			for (int coord = 0;coord < population.at(i).layout.size();) {
				//preventing the comparison to the coordinate itself
				if (j == coord) {
					coord++;
					continue;
				}
				// checks if the x and y values are NOT within the violation distance
				// off the corresponding coordinate
				// Both values, x and y, must be within that range
				// either under or above the given coordinate
				// Each "successfull" if branch proves that no violation exists
				// for this pair, and thereby continues to the next coordinate /
				// iteration
				if (population.at(i).layout.at(j).x < population.at(i).layout.at(coord).x - radius) {
					coord++;
					continue;
				}

				if (population.at(i).layout.at(j).x > population.at(i).layout.at(coord).x + radius) {
					coord++;
					continue;
				}

				if (population.at(i).layout.at(j).y < population.at(i).layout.at(coord).y - radius) {
					coord++;
					continue;
				}

				if (population.at(i).layout.at(j).y > population.at(i).layout.at(coord).y + radius) {
					coord++;
					continue;
				}

				// violation occured:
				// The violation is proven if no if branch above is triggered
				// the violating coordinate will be randomly replaced, and all
				// other coordinates within the individual will be checked against
				// the new one (coord = 0)

				population.at(i).layout.at(j).x = wscenario.width * (double) rand() / (double) RAND_MAX;
				population.at(i).layout.at(j).y = wscenario.height * (double) rand() / (double) RAND_MAX;
				coord = 0;
			}

		}
	}

}


