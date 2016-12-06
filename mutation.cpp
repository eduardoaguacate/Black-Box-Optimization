
#include <random>

#include "mutation.hpp"

namespace mutation {
   void none(individual&, KusiakLayoutEvaluator&) {}

   void creep(double range, double width, double height,
              individual& indiv, KusiakLayoutEvaluator& kle) {
      // prepare the rng
      std::random_device device;
      std::default_random_engine engine(device());
      // prepare a cauchy distribution
      std::cauchy_distribution<double> dist(-range, range);

      // apply the randomization to each coordinate pair in the layout
      for (auto& coords : indiv.layout) {
         coords.x += dist(engine);
         // enforce the layout width
         // if violated, the coordinate will wrap around the x-axis
         if (coords.x < 0.0) {
            coords.x += width;
         } else if (coords.x > width) {
            coords.x -= width;
         }
         
         coords.y += dist(engine);
         // enforce the layout height
         // if violated, the coordinate will wrap around the y-axis
         if (coords.y < 0.0) {
            coords.y += height;
         } else if (coords.y > height) {
            coords.y -= height;
         }
      }
   }

   void random_reset(float chance, double width, double height,
                     individual& indiv, KusiakLayoutEvaluator& kle) {
      // prepare the rng
      std::random_device device;
      std::default_random_engine engine(device());
      // prepare the distributions
      std::uniform_real_distribution<float> cdist(0.f, 1.f);
      std::uniform_real_distribution<double> wdist(-width, width);
      std::uniform_real_distribution<double> hdist(-height, height);

      // go through each coordinate pair in the layout
      for (auto& coords : indiv.layout) {
         // with probability = chance, a coordinate will be reset
         if (cdist(engine) <= chance) {
            coords.x = wdist(engine);
         }
         if (cdist(engine) <= chance) {
            coords.y = hdist(engine);
         }
      }
   }
}
