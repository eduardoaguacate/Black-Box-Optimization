#include <random>
#include <vector>
#include <fstream>
#include "functions.hpp"

namespace functions {
   std::vector<individual> load_population_from_file(const string file_name){
      std::ifstream file(file_name, std::ifstream::in);
      if (file.is_open()){
         int pop_size;
         file >> pop_size;
         std::vector<individual> pop;
         for (int i = 0; i < pop_size; ++i){
            individual indiv;
            file >> indiv.fitness;
            file >> indiv.phi;
            file >> indiv.rw;
            pop.push_back(indiv);
         }
         file.close();
         return pop;

      } else {
         std::cout << "ERROR: shouldLoadFile option is TRUE but the file was not found"
                   << std::endl;
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
         const individual& indiv = *it;
         file << indiv.fitness << "\r\n";
         file << indiv.phi << "\r\n";
         file << indiv.rw << "\r\n";
      }
      file.close();

   }
   
   bool turbine_valid(Scenario& scenario, double x, double y) {
      if (x < 0.0 || x > scenario.width)
         return false;

      if (y < 0.0 || y > scenario.height)
         return false;

      for (int o = 0; o < scenario.obstacles.rows; ++o) {
         if (x >= scenario.obstacles.get(o, 0) &&
             x <= scenario.obstacles.get(o, 2) &&
             y >= scenario.obstacles.get(o, 1) &&
             y <= scenario.obstacles.get(o, 3)) {
            return false;
         }
      }
      return true;
   }      
   
   Matrix<double> individual_to_matrix(Scenario& scenario, double phi, double rw) {
      // create turbines along the rows determined by phi (angle) and rw (row width)
      std::vector<std::pair<double, double>> coords;
      for (double x = 0.0; x < scenario.width; x += rw) {
         double sy = x * std::cos(phi);
         for (double y = sy; y < scenario.height; y += scenario.R * 8.0001) {
            if (turbine_valid(scenario, x, y)) {
               coords.push_back({ x, y });
            }
         }
      }

      // to hold the result
      Matrix<double> matrix(coords.size(), 2);;
      // to keep track of the turbine count
      int i = 0;
      for (auto& coord : coords) {
         matrix.set(i, 0, coord.first);
         matrix.set(i, 1, coord.second);
         i++;
      }
      return matrix;
   }
   
   bool compare_fitness(const individual &indiv,const individual &indiv2) {
      return (indiv.fitness > indiv2.fitness);
   }
}
