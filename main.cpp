/*  main.cpp
 *
 *   This is the class in which the evolutionary algorithm is going to be run.
 *   Version: 1.0.0
 */

//STL libraries
#include <iostream>
#include <vector>
#include <algorithm>
#include "math.h"

//API libraries
#include "API/WindScenario.h"
#include "API/KusiakLayoutEvaluator.h"

//Project's libraries
#include "structures.hpp"
#include "initialization.cpp"
#include "selection.hpp"
#include "recombination.hpp"
#include "mutation.hpp"
#include "replacement.hpp"

int main(int argc, const char * argv[]) {

        string scenario_path = "Scenarios/00.xml";
        WindScenario wscenario(scenario_path);
        KusiakLayoutEvaluator evaluator;
        evaluator.initialize(wscenario);

        std::vector<individual> population =
                initialization::initialization_2(evaluator,wscenario);

        for (auto it = population.begin(); it < population.end(); it++){
          cout << it->fitness << endl;
        }



}
