#include "initialization.hpp"

#include <cmath>
#include <limits>
#include <random>
#include <vector>

namespace initialization {
   std::vector<individual> init(const Scenario& scenario, int pop_size) {
      // prepare the rng
      std::random_device device;
      std::default_random_engine engine(device());
      // prepare the distributions
      std::uniform_real_distribution<double> phi_dist(0, M_PI / 2);
      std::uniform_real_distribution<double> rw_dist(scenario.R * 8.001, scenario.R * 16.001);
      
      std::vector<individual> population(pop_size);
      for (auto& indiv : population) {
         indiv.phi = phi_dist(engine);
         indiv.rw = rw_dist(engine);
         indiv.fitness = std::numeric_limits<double>::max();
      }      
      return population;
   }
}
