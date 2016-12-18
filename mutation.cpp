#include <algorithm>
#include <random>

#include "mutation.hpp"
#include "functions.hpp"

namespace mutation {
   void none(individual&, KusiakLayoutEvaluator&) {}

   void creep(double range, individual& indiv, KusiakLayoutEvaluator& kle) {
      // This is the min distance among turbines that must be satisfied
      double min_distance = 8.0 * kle.scenario.R;
      // the scenario dimensions
      double width = kle.scenario.width;
      double height = kle.scenario.height;

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
	 double x, y;
	 do {
	    x = coords.x + dist(engine);
	    // enforce the layout width
	    // if violated, the coordinate will wrap around the x-axis
	    if (x < 0.0) {
	       x += width;
	    } else if (x > width) {
	       x -= width;
	    }
         
	    y = coords.y + dist(engine);
	    // enforce the layout height
	    // if violated, the coordinate will wrap around the y-axis
	    if (y < 0.0) {
	       y += height;
	    } else if (y > height) {
	       y -= height;
	    }
	 }
	 while (functions::turbine_collides(x, y, kle, new_layout));
	 new_layout.push_back({ x, y });
      }
      
      indiv.layout = new_layout;
   }

   void random_reset(float chance, individual& indiv, KusiakLayoutEvaluator& kle) {      
      // This is the min distance among turbines that must be satisfied
      double min_distance = 8.0 * kle.scenario.R;
      // the scenario dimensions
      double width = kle.scenario.width;
      double height = kle.scenario.height;
         
      // prepare the rng
      std::random_device device;
      std::default_random_engine engine(device());
      // prepare the distributions
      std::uniform_real_distribution<float> cdist(0.f, 1.f);
      std::uniform_real_distribution<double> wdist(0.0, width);
      std::uniform_real_distribution<double> hdist(0.0, height);

      std::vector<coordinate> new_layout;
      // go through each coordinate pair in the layout
      for (auto& coords : indiv.layout) {
	 do {
	    // with probability = chance, a coordinate will be reset
	    if (cdist(engine) <= chance) {
	       coords.x = wdist(engine);
	       coords.y = hdist(engine);
	    }
	 }
	 while (functions::turbine_collides(coords.x, coords.y, kle, new_layout));
	 new_layout.push_back(coords);
      }
      
      indiv.layout = new_layout;
   }
}
