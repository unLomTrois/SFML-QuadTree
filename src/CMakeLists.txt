# include
include_directories(${PROJECT_SOURCE_DIR}/include/)
include_directories(${PROJECT_SOURCE_DIR}/include/random/effolkronium/include/)

# find SFML
find_package(SFML 2.5.1 COMPONENTS graphics window REQUIRED)

# find effolkronium random
find_package(effolkronium_random REQUIRED)

# application
add_library(application STATIC application.cpp point.cpp)
target_link_libraries(application sfml-graphics effolkronium_random)

# executable
add_executable(quadtree main.cpp)
target_link_libraries(quadtree application)
 