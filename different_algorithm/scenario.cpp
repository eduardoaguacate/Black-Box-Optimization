#include "scenario.hpp"

Scenario::Scenario(CompetitionScenario& cs)
   : width(cs.width),
     height(cs.height),
     R(cs.R),
     obstacles(cs.obstacles) {}

Scenario::Scenario(WindScenario& ws)
   : width(ws.width),
     height(ws.height),
     R(ws.R),
     obstacles(ws.obstacles) {}
