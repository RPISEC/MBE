cmake_minimum_required(VERSION 2.8)

# Adds an executable target
add_executable(lab1C lab1C.c)

add_executable(lab1B lab1B.c)
SET_FLAGS(lab1B "-s")

add_executable(lab1A lab1A.c)
SET_FLAGS(lab1A "-s")

# These are the files we want to give students
install(TARGETS lab1C lab1B lab1A DESTINATION "${RELEASE_DIR}/lab01")
