#include <random>
#include <vector>
#include "initialization.hpp"
#include <stdlib.h>
#include <time.h>

namespace initialization {

/* initialization_1
 *
 * This function takes  the WindScenario as parameter and produces
 * a population / vector of those turbine layouts.
 * The returned layouts are completely random based and
 * will be corrected by the "replaceviolations" function
 *
 * !! srand(time(0)); needs to be in the main function !!
 * !! currently no evaluation of the population implemented !
 !
 * parameters: WindScenario swscenario, int pop_size
 * return: std::vector<individual> population
 *
 */
std::vector<individual> initialization_1(WindScenario wscenario,int pop_size) {

	std::vector<individual> population;
	individual indiv;
	coordinate coord;


	for (int j = 0; j < pop_size;j++){
		//initiate layout (coordinates)
		for (int i = 0;i < wscenario.nturbines; i++) {
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
 * constraints from the WindScenario as parameters, and automatically corrects
 * all turbine positions within the given population by new
 * random positions. No return value.
 *
 * parameters: std::vector<individual> &population
 * 			   double radius, int width, int height
 *
 * return: void
 */
void replace_violations(std::vector<individual> &population,WindScenario wscenario) {
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
individual create_individual_2(KusiakLayoutEvaluator &evaluator,
                               WindScenario &wscenario){
        // There is a security constraint between turbines, they can't be
        // less than 8R near, which means that they have to be more than
        // 8R far away from each other
        double min_distance = 8.0 * wscenario.R;
        double factor = min_distance * 1.000001;
        // These are the farm's constraints
        double width = wscenario.width / factor;
        double height = wscenario.height / factor;

        int n_turbines = wscenario.nturbines;

        // We are going to prepare a random number generator, to generate
        // randomly the positions of the turbines
        std::random_device device;

        // Random-number engine used (Mersenne-Twister in this case)
        std::mt19937 rng(device());

        //We are going to randomly generate the coordinates of the turbines
        int count = 0;
        std::uniform_real_distribution<double> dist_width(0.1,width * 1.0);
        std::uniform_real_distribution<double> dist_height(0.1,height * 1.0);
        std::vector<coordinate> layout;
        // We create all the turbines
        while (count < n_turbines) {
                double x = dist_width(rng) * factor;
                double y = dist_height(rng) * factor;
                // Checks if the coordinate generated collides with any other
                // turbine
                if(!functions::turbine_collides(x,y,min_distance,layout)) {
                        struct coordinate coord = {
                                x, //x coordinate
                                y, //y coordinate
                        };

                        layout.push_back(coord);
                        count++;
                }
        };
        // We calculate the fitness of the individual, or the layout
        Matrix<double> mat_layout = functions::individual_to_matrix<double>(layout);
        double individual_fitness = evaluator.evaluate_2014(&mat_layout);
        struct individual indiv = {
                layout, // The std::vector<coordinate>
                individual_fitness, // The fitness calculated by the evaluator
        };
        return indiv;
}

std::vector<individual> initialization_2(KusiakLayoutEvaluator &evaluator,
                                         WindScenario &wscenario){

        std::vector<individual> population;
        // This is population number, which is the number of layouts or
        // individual_fitness we are going to have per generation

        int num_population = 30;

        // We start populating
        for(int i = 0; i < num_population; ++i) {
                struct individual indiv =
                        initialization::create_individual_2(evaluator,wscenario);
                population.push_back(indiv);
        }

        return population;
}

}
