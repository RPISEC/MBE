# RPISEC copyright/license should go here

cmake_minimum_required(VERSION 2.8)

project(MBE)
enable_testing()
include_directories("./include")

# Settings
set(MBE_FLAGS "-m32 -O0 -fno-inline-functions")
set(DISABLE_DEP_FLAG "-z execstack")
set(DISABLE_RELRO_FLAG "-z norelro")
set(DISABLE_CANARY_FLAG "-fno-stack-protector")
set(NO_MITS_FLAGS "${DISABLE_DEP_FLAG} ${DISABLE_RELRO_FLAG} ${DISABLE_CANARIES_FLAG}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${MBE_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MBE_FLAGS}")

# Handy macro
MACRO(SUBDIRLIST result curdir)
  FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
  SET(dirlist "")
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${curdir}/${child})
        LIST(APPEND dirlist ${child})
    ENDIF()
  ENDFOREACH()
  SET(${result} ${dirlist})
ENDMACRO()

MACRO(SET_FLAGS target flags)
  SET_TARGET_PROPERTIES(${target} PROPERTIES COMPILE_FLAGS ${flags})
  SET_TARGET_PROPERTIES(${target} PROPERTIES LINK_FLAGS ${flags})
ENDMACRO()

# Where the files students get will go (install dir)
set(RELEASE_DIR "${CMAKE_BINARY_DIR}/release")

### Build the code ###
add_subdirectory(src)
