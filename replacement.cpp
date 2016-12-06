#include <random>
#include <vector>
#include <algorithm>
#include "replacement.hpp"

namespace replacement {
std::vector<individual> replacement_1(std::vector<individual> &old,
                                      std::vector<individual> &children){

        // The new population
        std::vector<individual> new_population;

        // We sort both vectors according to their fitnesses
        std::sort (old.begin(), old.end(), functions::compare_fitness);
        std::sort (children.begin(), old.end(), functions::compare_fitness);

        // We initialize the random number generator
        Random rand;

        //We select the 10 most fitted members from the parents
        for (auto it = old.end() - 1; it > old.begin() + 19; --it) {
                new_population.push_back(*it);
                old.erase(it);
        }

        //We select the 10 most fitted members from the children
        for (auto it = children.end() - 1; it > children.begin() + 19; --it) {
                new_population.push_back(*it);
                old.erase(it);
        }

        // We select five random numbers from both vectors
        for (int i = 0; i < 5; ++i) {

                // We randomly get a position from the parents
                auto it = old.begin() + rand.DrawNumber(0,old.size() - 1);
                new_population.push_back(*it);

                //We erase this element so that we dont push back repeated parents
                old.erase(it);

                // We randomly get a position from the children
                it = children.begin() + rand.DrawNumber(0,children.size() - 1);
                new_population.push_back(*it);

                //We erase this element so that we dont push back repeated children
                children.erase(it);

        }

        return new_population;
}
}
