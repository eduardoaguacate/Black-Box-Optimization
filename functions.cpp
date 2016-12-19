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

bool compare_fitness(const individual &indiv,const individual &indiv2) {
    return (indiv.fitness > indiv2.fitness);
   }
}
