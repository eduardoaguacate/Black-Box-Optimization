#include <random>
#include <vector>
#include <fstream>
#include "functions.hpp"

namespace functions {
   bool turbine_collides(double x, double y,
                         Scenario &scenario,
                         std::vector<coordinate> &layout){
    
       // We check first whether the coordinate collides with an obstacle
       if (functions::coordinateCollidesWithObstacles(x, y, scenario)){
           return true;
       }
       // Turbine does not collide with any obstacle, then we are good to go
       else{
           // The minimum distance so that they are in the center
           double min_distance = 8.0 * scenario.R;
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
   }
    
    bool coordinateCollidesWithObstacles(double x, double y, Scenario& scenario){
        // We check whether this coordinate collide with a given obstacle
        for (int o = 0; o < scenario.obstacles.rows; o++) {
            Matrix<double> matObstacles = scenario.obstacles;
            // If somehow the position of a turbine is within the range
            // of an obstacle, then it collides, and it's an invalid turbine
            double xmin = matObstacles.get(o, 0);
            double ymin = matObstacles.get(o, 1);
            double xmax = matObstacles.get(o, 2);
            double ymax = matObstacles.get(o, 3);
            if (x > xmin &&
                x < xmax &&
                y > ymin &&
                y < ymax) {
                return true;
            }
        }
        
        return false;
    }


   void remove_illegal_coordinates(individual& indiv, Scenario& scenario) {
      // return if there are no obstacles in the scenario
      if (scenario.obstacles.rows == 0)
         return;

      // iterate through all turbines, and remove the ones which are on obstacles
      for (auto it = indiv.layout.begin(); it != indiv.layout.end();) {
         bool removed = false;
         for (int o = 0; o < scenario.obstacles.rows; ++o) {
            if (it->x >= scenario.obstacles.get(o, 0) &&
                it->x <= scenario.obstacles.get(o, 2) &&
                it->y >= scenario.obstacles.get(o, 1) &&
                it->y <= scenario.obstacles.get(o, 3)) {
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
    std::vector<individual> load_population_from_file(const string file_name){
        std::ifstream file(file_name, std::ifstream::in);
        if (file.is_open()){
            int pop_size;
            file >> pop_size;
            std::vector<individual> pop;
            for (int i = 0; i < pop_size; ++i){
                individual indiv;
                double fitness;
                int layout_size;
                file >> fitness;
                file >> layout_size;
                indiv.fitness = fitness;
                for (int j = 0; j < layout_size; ++j){
                    coordinate coord;
                    file >> coord.x >> coord.y;
                    indiv.layout.push_back(coord);
                }
                pop.push_back(indiv);
            }
            file.close();
            return pop;

        }
        else{
            std::cout << "ERROR: shouldLoadFile option is TRUE but the file was not found" << std::endl;
            return std::vector<individual>();
        }

    }
    
    void save_population_to_file(const string file_name,
                                 std::vector<individual> &pop){
        // We make the file
        std::ofstream file(file_name);
        
        /*
         * FILE STRUCTURE
         1. pop_size
         (loop)2..pop_size
                lineX. individual fitness
                lineY. individual's layout size
                (loop)lineY..individual's layout size
                    lineZ. x      y
         
         */
        
        file << pop.size() << "\r\n";
        // We loop through all the individuals in the population
        for (auto it = pop.begin(); it < pop.end(); ++it){
            individual indiv = *it;
            std::vector<coordinate> layout = indiv.layout;
            file << indiv.fitness << "\r\n";
            file << layout.size() << "\r\n";
            // We loop through the layout of the individual
            for (auto it2 = layout.begin(); it2 < layout.end(); ++it2){
                file << it2->x << " " << it2->y << "\r\n";
            }
        }
        file.close();

    }


   bool compare_fitness(const individual &indiv,const individual &indiv2) {
      return (indiv.fitness > indiv2.fitness);
   }
}
