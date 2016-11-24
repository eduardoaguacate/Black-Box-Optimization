/*  main.cpp
*
*   This is the class in which the evolutionary algorithm is going to be run.
*   Version: 1.0.0
*/

//STL libraries
#include <bits/stdc++.h>

//API libraries
#include "API/WindScenario.h"
#include "API/KusiakLayoutEvaluator.h"

//Project's libraries
#include "structures.hpp"
#include "initialization.hpp"
#include "selection.hpp"
#include "recombination.hpp"
#include "mutation.hpp"
#include "replacement.hpp"

int main(int argc, const char * argv[]) {

  WindScenario wscenario(argv[1]);
  KusiakLayoutEvaluator evaluator;
  evaluator.initialize(wscenario);

}
