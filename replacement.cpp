#include <random>
#include <vector>
#include <algorithm>
#include "replacement.hpp"

namespace replacement {
   std::vector<individual> replacement_1(std::vector<individual> &old,
                                         std::vector<individual> &children,
                                         int num_population){
      // The new population
      std::vector<individual> new_population;

      // We sort both vectors according to their fitnesses
      std::sort (old.begin(), old.end(), functions::compare_fitness);
      std::sort (children.begin(), children.end(), functions::compare_fitness);

      // We initialize the random number generator
      Random rand;

      // This fraction is used in order to start on the 2/3'th part of the
      // vector, to get the 1/3 part of it.
      int fraction = (2.0 / 3.0) * num_population;
      //We select the 1/3 of the most fitted members from the parents
      for (auto it = old.end() - 1; it > old.begin() + (fraction - 1) ; --it) {
         new_population.push_back(*it);
         old.erase(it);
      }

      //We select 1/3 of the most fitted members from the children
      for (auto it = children.end() - 1; it > children.begin() + (fraction - 1); --it) {
         new_population.push_back(*it);
         children.erase(it);
      }

      // We select the 1/3 of the new population by adding it to the vector
      // until we reach num_population
        
      // We use this sentinel to alternate the fill in of the new population vector
      int i = 0;
        
      // We make a random mod number so that the new population isn't biased
      // towards always having more children or more of the old population
      int mod = rand.DrawNumber<int>(0, 1);
      while(new_population.size() <  num_population){
         if (!old.empty() && i % 2 == mod){
            // We randomly get a position from the parents
            auto it = old.begin() + rand.DrawNumber<int>(0,old.size() - 1);
            new_population.push_back(*it);
            //We erase this element so that we dont push back repeated parents
            old.erase(it);
         }
            
         if (!children.empty() && i % 2 == (mod - 1) ){
            // We randomly get a position from the children
            auto it = children.begin() + rand.DrawNumber<int>(0,children.size() - 1);
            new_population.push_back(*it);
                
            //We erase this element so that we dont push back repeated children
            children.erase(it);
         }
         i++;
      }
        
      return new_population;
   }

   std::vector<individual> age_based(std::vector<individual>& old,
                                     std::vector<individual>& children,
                                     int num_population) {
      return children;
   }
}
