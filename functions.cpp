#include <random>
#include <vector>
#include "functions.hpp"

namespace functions {
bool turbine_collides(double x, double y, double min_distance,
                      std::vector<coordinate> &layout){
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
        }
        return false;
}

bool compare_fitness(const individual &indiv,const individual &indiv2) {
        return (indiv.fitness < indiv2.fitness);
   }
}
