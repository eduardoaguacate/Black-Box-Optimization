#include <algorithm>
#include <random>

#include "functions.hpp"
#include "recombination.hpp"

namespace recombination {
   std::vector<individual> none(const std::vector<std::vector<individual>::iterator>& parents,
                                Scenario& scenario) {      
      std::vector<individual> children;
      // just copy all the parents
      for (auto& parent : parents) {
         children.push_back(*parent);
      }
      return children;
   }
   
   std::vector<individual> crossover(const std::vector<std::vector<individual>::iterator>& parents,
                                     Scenario& scenario) {
      std::vector<individual> children;
      // combine each parent with the one next to it
      for (auto it = parents.begin(); it != parents.end(); ++it) {
         auto& p_a = *(it);
         auto& p_b = it + 1 == parents.end() ? *(parents.begin()) : *(it + 1);
         double phi_avg = (p_a->phi + p_b->phi) / 2;
         double rw_avg = (p_a->rw + p_b->rw) / 2;
         children.push_back({ phi_avg, rw_avg, 0.0 });
      }
      return children;
   }
}
