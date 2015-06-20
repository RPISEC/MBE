cmake_minimum_required(VERSION 2.8)

# Adds an executable target
add_executable(lab2C lab2C.c)
SET_FLAGS(lab2C "-O0 -fno-stack-protector")

add_executable(lab2B lab2B.c)
SET_FLAGS(lab2B "-O0 -fno-stack-protector")

add_executable(lab2A lab2A.c)
SET_FLAGS(lab2A "-O0 -fno-stack-protector")

# These are the files we want to give students
install(TARGETS lab2C lab2B lab2A DESTINATION "${RELEASE_DIR}/lab02")
install(FILES lab2C.c lab2B.c lab2A.c DESTINATION "${RELEASE_DIR}/lab02")
