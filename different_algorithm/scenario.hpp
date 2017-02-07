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

   /*
    * the maximum number of turbines which a layout can have in this scenario
    * (CompetitionScenario doesn't have the nturbines attribute)
    * this is calculated as follows:
    * area = width * height
    * areaObstacles = sum of area of all obstacles
    * maxTurbines = (area - areaObstacles) / (PI*R^2)
    */
   int max_turbines;
   double width;
   double height;
   double R;
   Matrix<double>& obstacles;

private:
   int calculate_max_turbines();
};

#endif
