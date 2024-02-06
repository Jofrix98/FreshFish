# Version minimale de CMake requise
cmake_minimum_required(VERSION 3.12)

project(FreshFish)

find_package(PkgConfig)
pkg_check_modules(RSVG librsvg-2.0)

# Core sources
file(GLOB CORE_SRC src/*.cpp src/*.hpp)
list(REMOVE_ITEM CORE_SRC test_routes.cpp)
list(REMOVE_ITEM CORE_SRC test_partie.cpp)
add_library(core STATIC ${CORE_SRC})
link_libraries(core)

add_compile_definitions(FF_ROOT="${CMAKE_SOURCE_DIR}/assets/")

if(RSVG_FOUND)
  # Inclusion des headers de librsvg pour les routes
  include_directories(${RSVG_INCLUDE_DIRS})
  link_libraries(${RSVG_LINK_LIBRARIES})
else()
  add_compile_definitions(NO_GRAPHICS)
endif()

# Applications
add_executable(test_graphe src/test_graphe.cpp)
add_executable(test_routes src/test_routes.cpp)
add_executable(test_partie src/test_partie.cpp)
