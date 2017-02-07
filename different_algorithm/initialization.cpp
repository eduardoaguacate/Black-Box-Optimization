#include "initialization.hpp"

#include <cmath>
#include <random>
#include <vector>

namespace initialization {
   std::vector<individual> init(WindFarmLayoutEvaluator& evaluator,
                                Scenario& scenario,
                                int pop_size) {
      // prepare the rng
      std::random_device device;
      std::default_random_engine engine(device());
      // prepare the distributions
      std::uniform_real_distribution<double> phi_dist(0, M_PI / 2);
      std::uniform_real_distribution<double> rw_dist(scenario.R * 8.001, scenario.R * 16.001);
      
      std::vector<individual> individuals;
      for (int i = 0; i < pop_size; ++i) {
         double phi = phi_dist(engine);
         double rw = rw_dist(engine);
         Matrix<double> matrix = functions::individual_to_matrix(scenario, phi, rw);
         double fitness = evaluator.evaluate(&matrix);
         individuals.push_back({ phi, rw, fitness });
      }
      
      return individuals;
   }
}
