#include <random>
#include <vector>
#include "initialization.hpp"

namespace initialization {

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

        /* We are going to prepare a random number generator, to generate
         * the number of turbines that are going to be used in the current
         * layout */
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
