#include "mutation.hpp"

#include <algorithm>
#include <random>

namespace mutation {
   void incremental(double chance, individual& indiv, Scenario& scenario) {
      // the minimum row distance
      double min_rw = scenario.R * 8.0001;
      // prepare the rng
      std::random_device device;
      std::default_random_engine engine(device());
      // prepare the distributions
      std::uniform_real_distribution<double> phi_dist(-M_PI / 16, M_PI / 16);
      std::uniform_real_distribution<double> rw_dist(-scenario.R / 4, scenario.R / 4);

      indiv.phi += phi_dist(engine);
      if (indiv.phi < 0.0)
         indiv.phi += M_PI / 2;
      if (indiv.phi > M_PI / 2)
         indiv.phi -= M_PI / 2;
      indiv.rw += rw_dist(engine);
      if (indiv.rw < min_rw)
         indiv.rw = min_rw;
      if (indiv.rw > min_rw * 2)
         indiv.rw = min_rw * 2;
   }
}
