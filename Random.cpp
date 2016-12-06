#include <random>
#include <vector>
#include <algorithm>
#include <Random.hpp>

Random::Random (){
  // The random device for the random numbers
  std::random_device device;

  // Random-number engine used (Mersenne-Twister in this case)
  std::mt19937 rng(device());
  mt19937_eng = rng;

}

int Random::DrawNumber(int min, int max)
{
        // The uniform int distribution is created
        std::uniform_int_distribution<int> distribution(min,max);
        return distribution(mt19937_eng);
}
