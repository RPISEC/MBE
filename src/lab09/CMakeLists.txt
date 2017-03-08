cmake_minimum_required(VERSION 2.8)

# Adds an executable target
add_executable(lab9C lab9C.cpp)
SET_FLAGS(lab9C "-fstack-protector-all -z relro -z now")

add_executable(lab9A lab9A.cpp)
SET_FLAGS(lab9A "-fstack-protector-all -z relro -z now -fPIE -pie")

# These are the files we want to give students
install(TARGETS lab9C lab9A DESTINATION "${RELEASE_DIR}/lab09")
install(FILES lab9C.cpp lab9C.readme lab9A.cpp lab9A.readme DESTINATION "${RELEASE_DIR}/lab09")
