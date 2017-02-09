#include <random>
#include <vector>
#include <fstream>
#include "functions.hpp"

namespace functions {      
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
   
   Matrix<double> individual_to_matrix(Scenario& scenario, const individual& indiv) {
      // create turbines along the rows determined by phi (angle) and rw (row width)
      std::vector<std::pair<double, double>> coords;
      double min_rw = scenario.R * 8.0001;
      double erw = std::max(min_rw, std::abs(indiv.rw * std::sin(indiv.phi)));
      double erh = std::max(min_rw, std::abs(indiv.rw * std::cos(indiv.phi)));
      for (double x = 0.0; x < scenario.width; x += erw) {
         double sy = x * std::tan(indiv.phi);
         while (sy > erh) {
            sy -= erh;
         }
         for (double y = sy; y < scenario.height; y += erh) {
            if (turbine_valid(scenario, x, y)) {
               coords.push_back({ x, y });
            }
         }
      }

      // to hold the result
      Matrix<double> matrix(coords.size(), 2);
      // to keep track of the turbine count
      int i = 0;
      for (auto& coord : coords) {
         matrix.set(i, 0, coord.first);
         matrix.set(i, 1, coord.second);
         i++;
      }
      return matrix;
   }
   
   void evaluate_population(WindFarmLayoutEvaluator& evaluator, Scenario& scenario,
                            std::vector<individual>& population) {
      for (auto& indiv : population) {
         Matrix<double> matrix = individual_to_matrix(scenario, indiv);
         indiv.fitness = evaluator.evaluate(&matrix);
      }
   }
   
   bool compare_fitness(const individual& a, const individual& b) {
      return (a.fitness > b.fitness);
   }
   
   std::vector<individual> load_population_from_file(const std::string& file_name) {
      std::ifstream file(file_name, std::ifstream::in);
      if (file.is_open()) {
         int pop_size;
         file >> pop_size;
         std::vector<individual> pop(pop_size);
         for (auto& indiv : pop) {
            file >> indiv.fitness;
            file >> indiv.phi;
            file >> indiv.rw;
         }
         file.close();
         return pop;
      } else {
         std::cout << "ERROR: shouldLoadFile option is TRUE but the file was not found"
                   << std::endl;
         return std::vector<individual>();
      }
   }
    
   void save_population_to_file(const std::string& file_name, const std::vector<individual>& pop) {
      // We make the file
      std::ofstream file(file_name);   
      /*
       * FILE STRUCTURE
       1. pop_size
       (loop)2..pop_size
       lineX. individual fitness
       lineY. angle phi
       lineZ. row width
      */   
      file << pop.size() << "\r\n";
      // We loop through all the individuals in the population
      for (auto& indiv : pop){
         file << indiv.fitness << "\r\n";
         file << indiv.phi << "\r\n";
         file << indiv.rw << "\r\n";
      }
      file.close();
   }
}
