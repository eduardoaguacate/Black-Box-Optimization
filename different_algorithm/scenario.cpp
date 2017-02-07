#include "scenario.hpp"
#include <cmath>

Scenario::Scenario(CompetitionScenario& cs)
   : width(cs.width),
     height(cs.height),
     R(cs.R),
     obstacles(cs.obstacles) {
   
   max_turbines = calculate_max_turbines();
}

Scenario::Scenario(WindScenario& ws)
   : width(ws.width),
     height(ws.height),
     R(ws.R),
     obstacles(ws.obstacles) {
   
   max_turbines = calculate_max_turbines();
}

int Scenario::calculate_max_turbines() {
   double base_area = width * height;
   for (int o = 0; o < obstacles.rows; ++o) {
      double obs_width = obstacles.get(o, 2) - obstacles.get(o, 0);
      double obs_height = obstacles.get(o, 3) - obstacles.get(o, 1);
      base_area -= obs_width * obs_height;
   }
   double turb_area = std::pow(R * 8.0001, 2) * M_PI / 2;
   return base_area / turb_area;
}
