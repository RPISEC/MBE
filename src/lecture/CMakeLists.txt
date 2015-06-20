cmake_minimum_required(VERSION 2.8)

set(RELEASE_DIR "${RELEASE_DIR}/lecture")

# Adds all of the level directories
SUBDIRLIST(SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR})
foreach(subdir ${SUBDIRS})
  message(STATUS "Building lecture:${subdir}...")
  add_subdirectory(${subdir})
endforeach()
