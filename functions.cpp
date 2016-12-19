#include <random>
#include <vector>
#include "functions.hpp"

namespace functions {
   bool turbine_collides(double x, double y,
                         KusiakLayoutEvaluator &evaluator,
                         std::vector<coordinate> &layout){
    
      // The minimum distance so that they are in the center
      double min_distance = 8.0 * evaluator.scenario.R;
      for(auto it = layout.begin(); it < layout.end(); ++it) {
         // If there is already a coordinate with these values, then
         // it does collide
         if(it->x == x && it->y == y) {
            return true;
         }
         // We check the security distance constraint
         double dif_x = it->x - x;
         double dif_y = it->y - y;
         double dist = sqrt(pow(dif_x,2) + pow(dif_y,2));
         if (dist < min_distance) {
            return true;
         }
        
         // We check the obstacle constraint
         Matrix<double>& matObstacles = evaluator.scenario.obstacles;
         for (int j = 0; j < evaluator.scenario.obstacles.rows; j++) {
            // If somehow the position of a turbine is within the range
            // of an obstacle, then it collides, and it's an invalid turbine
            if (it->x > matObstacles.get(j, 0) &&
                it->x < matObstacles.get(j, 2) &&
                it->y > matObstacles.get(j, 1) &&
                it->y < matObstacles.get(j, 3)) {
               return true;
            }
         }
      }
      return false;
   }

   void remove_illegal_coordinates(individual& indiv, WindScenario& wscenario) {
      // return if there are no obstacles in the scenario
      if (wscenario.obstacles.rows == 0)
         return;

      // iterate through all turbines, and remove the ones which are on obstacles
      for (auto it = indiv.layout.begin(); it != indiv.layout.end();) {
         bool removed = false;
         for (int o = 0; o < wscenario.obstacles.rows; ++o) {
            if (it->x >= wscenario.obstacles.get(o, 0) &&
                it->x <= wscenario.obstacles.get(o, 2) &&
                it->y >= wscenario.obstacles.get(o, 1) &&
                it->y <= wscenario.obstacles.get(o, 3)) {
               removed = true;
               break;
            }
         }
         if (removed) {
            it = indiv.layout.erase(it);            
         } else {
            it++;
         }
      }
   }

   bool compare_fitness(const individual &indiv,const individual &indiv2) {
      return (indiv.fitness > indiv2.fitness);
   }
}
