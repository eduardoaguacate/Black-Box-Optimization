/*
 * scenario.hpp
 *
 * contains the definition of the scenario adapter
 */
#ifndef BBO_SCENARIO_HPP
#define BBO_SCENARIO_HPP

#include "API/CompetitionScenario.h"
#include "API/WindScenario.h"

/*
 * this class is an adapter for the different scenarios
 * initialize it with a CompetitionScenario or WindScenario,
 * then access the scenario attributes
 */
class Scenario {
public:
   Scenario(CompetitionScenario& cscenario);
   Scenario(WindScenario& wscenario);

   double width;
   double height;
   double R;
   Matrix<double>& obstacles;
};

#endif
