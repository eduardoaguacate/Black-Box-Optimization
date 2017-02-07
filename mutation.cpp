#include <algorithm>
#include <random>

#include "mutation.hpp"
#include "functions.hpp"

namespace mutation {
   void creep(double range, individual& indiv, Scenario& scenario) {
      // This is the min distance among turbines that must be satisfied
      double min_distance = 16.0 * scenario.R;
      // the scenario dimensions
      double width = scenario.width;
      double height = scenario.height;

      // the creep range must be at least the min distance, else we might get stuck
      if (range < 0.0) {
         range = std::min(range, -min_distance);
      } else {
         range = std::max(range, min_distance);
      }
      
      // prepare the rng
      std::random_device device;
      std::default_random_engine engine(device());
      // prepare a distribution
      std::uniform_real_distribution<double> dist(-range, range);

      std::vector<coordinate> new_layout;
      // apply the randomization to each coordinate pair in the layout
      for (auto& coords : indiv.layout) {
         double x = coords.x;
         double y = coords.y;
         do {
            x += dist(engine);
            // enforce the layout width
            // if violated, the coordinate will wrap around the x-axis
            if (x < 0.0) {
               x += width;
            } else if (x > width) {
               x -= width;
            }
         
            y += dist(engine);
            // enforce the layout height
            // if violated, the coordinate will wrap around the y-axis
            if (y < 0.0) {
               y += height;
            } else if (y > height) {
               y -= height;
            }
         } while (functions::turbine_collides(x, y, scenario, new_layout));
         new_layout.push_back({ x, y });
      }
      indiv.layout = new_layout;
   }

   void random_reset(float chance, individual& indiv, Scenario& scenario) {      
      // This is the min distance among turbines that must be satisfied
      double min_distance = 8.0 * scenario.R;
      // the scenario dimensions
      double width = scenario.width;
      double height = scenario.height;
         
      // prepare the rng
      std::random_device device;
      std::default_random_engine engine(device());
      // prepare the distributions
      std::uniform_real_distribution<float> cdist(0.f, 1.f);
      std::uniform_real_distribution<double> wdist(0.0, width);
      std::uniform_real_distribution<double> hdist(0.0, height); 
      // determine how many coordinates should be reset
      std::size_t size = indiv.layout.size();
      std::size_t rsize = size * chance;

      // copy the not to be reset coordinates
      std::vector<coordinate> new_layout;
      std::copy(indiv.layout.begin(), indiv.layout.begin() + rsize, 
         std::back_inserter(new_layout));
      // add the reseted coordinates
      for (std::size_t i = rsize; i < size; ++i) {
         double x;
         double y;
         do {
            x = wdist(engine);
            y = hdist(engine);
         } while (functions::turbine_collides(x, y, scenario, new_layout));
         new_layout.push_back({ x, y });
      }
      indiv.layout = new_layout;
   }
}
