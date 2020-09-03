# include
include_directories(${PROJECT_SOURCE_DIR}/include/)
include_directories(${PROJECT_SOURCE_DIR}/include/random/effolkronium/include/)

# find SFML
find_package(SFML 2.5.1 COMPONENTS graphics window REQUIRED)

# find effolkronium random
find_package(effolkronium_random REQUIRED)

add_library(quadtree STATIC point.cpp node.cpp)
target_link_libraries(quadtree sfml-graphics)

# application
add_library(application STATIC application.cpp)
target_link_libraries(application quadtree sfml-graphics effolkronium_random)

# executable
add_executable(sfml_quadtree main.cpp)
target_link_libraries(sfml_quadtree application)
 