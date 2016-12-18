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
    T DrawNumber(T min, T max);

  private:
      //The Mersenne Twister random number generator
      std::mt19937 mt19937_eng;
};

#endif
