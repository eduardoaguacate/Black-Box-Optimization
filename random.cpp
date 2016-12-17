#include <random>
#include <vector>
#include <algorithm>
#include "random.hpp"

Random::Random (){
  // The random device for the random numbers
  std::random_device device;

  // Random-number engine used (Mersenne-Twister in this case)
  std::mt19937 rng(device());
  mt19937_eng = rng;

}



