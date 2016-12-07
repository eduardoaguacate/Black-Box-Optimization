
project (BlackBoxOptimization)

set(CMAKE_CXX_STANDARD 11)

add_library(API API/tinyxml2.cpp API/WindScenario.cpp
  API/WindFarmLayoutEvaluator.cpp API/KusiakLayoutEvaluator.cpp)
add_library(functions functions.cpp)
add_library(random random.cpp)
add_library(initialization initialization.cpp)
add_library(selection selection.cpp)
add_library(recombination recombination.cpp)
add_library(mutation mutation.cpp)
add_library(replacement replacement.cpp)
add_library(evolutionary_algorithm evolutionary_algorithm.cpp)

add_executable (main main.cpp)
target_link_libraries(functions API)
target_link_libraries(initialization functions)
target_link_libraries(selection functions)
target_link_libraries(recombination functions)
target_link_libraries(mutation API)
target_link_libraries(replacement functions random)
target_link_libraries(evolutionary_algorithm API functions)
target_link_libraries(main evolutionary_algorithm initialization
  selection recombination mutation replacement)
