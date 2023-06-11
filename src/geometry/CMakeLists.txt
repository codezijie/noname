
file(GLOB_RECURSE GEO_SOURCES *.cpp)

add_library(app_geometry
  ${GEO_SOURCES}
) 