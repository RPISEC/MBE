cmake_minimum_required(VERSION 2.8)

# Adds an executable target
add_executable(lab4C lab4C.c)
SET_FLAGS(lab4C "${NO_MITS_FLAGS}")

add_executable(lab4B lab4B.c)
SET_FLAGS(lab4B "${NO_MITS_FLAGS}")

add_executable(lab4A lab4A.c)
SET_FLAGS(lab4A "-z execstack -z relro -z now")

# These are the files we want to give students
install(TARGETS lab4C lab4B lab4A DESTINATION "${RELEASE_DIR}/lab04")
install(FILES lab4C.c lab4B.c lab4A.c DESTINATION "${RELEASE_DIR}/lab04")

