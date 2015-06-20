cmake_minimum_required(VERSION 2.8)

# Adds all of the level directories
SUBDIRLIST(SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR})
foreach(subdir ${SUBDIRS})
  message(STATUS "Building ${subdir}...")
  add_subdirectory(${subdir})
endforeach()
