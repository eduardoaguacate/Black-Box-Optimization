// Random.hpp
//
// This class creates random numbers using the Mersenne Twister random number
// generator
//

#ifndef BBO_RANDOM_HPP
#define BBO_RANDOM_HPP

#include <random>

class Random {
  public:
    /* Random (constructor)
    *
    * This is the default constructor of the random number generator
    */
    Random();

    /* DrawNumber
    *
    * This function will randomly draw number from the given range, inclusive
    * using the uniform int distribution. The typename T is needed because based
    * on it, it's the uniform int distribution, or the uniform real distribution
    *
    * params:
    *       min: the lower bound
    *       max: the upper bound
    * return:
    *       T : a randomly generated number (the typename T) from min to max
    */
    template<typename T>
    T DrawNumber(int min, int max);

  private:
      //The Mersenne Twister random number generator
      std::mt19937 mt19937_eng;
};

template<typename T>
T Random::DrawNumber(int min, int max)
{
    // The typename T is verified
    if (strcmp(typeid(T).name(),"i") == 0){
        // The uniform int distribution is created
        std::uniform_int_distribution<int> distribution(min,max);
        return distribution(mt19937_eng);
    }
    else{
        // The uniform real distribution is created
        std::uniform_real_distribution<T> distribution(min,max);
        return distribution(mt19937_eng);
    }
}


#endif
