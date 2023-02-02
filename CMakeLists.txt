cmake_minimum_required(VERSION 3.23)
project(cupid)

include_directories(include)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        cupid main.cpp
        src/xml/pugixml.cpp src/geometry/coordinate.cpp src/osm/map.cpp src/osm/node.cpp src/osm/way.cpp src/osm/tag.cpp
        )
