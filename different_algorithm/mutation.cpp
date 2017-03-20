#include "mutation.hpp"

#include <algorithm>
#include <random>

namespace mutation {
   void incremental(individual& indiv, int r, Scenario& scenario) {
      // prepare the rng
      std::random_device device;
      std::default_random_engine engine(device());
      // prepare the distributions
      std::uniform_real_distribution<double> phi_dist(-M_PI / (2 * r), M_PI / (2 * r));
      std::uniform_real_distribution<double> rw_dist(-scenario.R / r, scenario.R / r);

      // the minimum angle
      double min_phi = 0.0;
      // the maxmimum angle
      double max_phi = M_PI / 2;
      // increase/decrease the angle phi
      indiv.phi += phi_dist(engine);
      // enforce the limits
      if (indiv.phi < min_phi) {
         indiv.phi += max_phi;
      } else if (indiv.phi > max_phi) {
         indiv.phi -= max_phi;
      }
      
      // the minimum row distance
      double min_rw = scenario.R * 8.0001;
      // the maxmimum row distance
      double max_rw = scenario.R * 16.0001;
      // increase/decrease the row width
      indiv.rw += rw_dist(engine);
      // enforce the limits
      if (indiv.rw < min_rw) {
         indiv.rw = min_rw;
      } else if (indiv.rw > max_rw) {
         indiv.rw = max_rw;
      }
   }
}
