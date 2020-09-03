# include
include_directories(${PROJECT_SOURCE_DIR}/include/)

# find SFML
set(SFML_DIR ${PROJECT_SOURCE_DIR}/lib/SFML-2.5.1/lib/cmake/SFML)
find_package(SFML 2.5.1 COMPONENTS graphics window REQUIRED)

# application
add_library(application STATIC app.cpp point.cpp random.cpp)
target_link_libraries(application sfml-graphics)

# executable
add_executable(quadtree main.cpp)
target_link_libraries(quadtree application)
 