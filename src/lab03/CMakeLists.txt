cmake_minimum_required(VERSION 2.8)

# Adds an executable target
add_executable(lab3C lab3C.c)
SET_FLAGS(lab3C "${NO_MITS_FLAGS}")

add_executable(lab3B lab3B.c)
SET_FLAGS(lab3B "${NO_MITS_FLAGS}")

add_executable(lab3A lab3A.c)
SET_FLAGS(lab3A "${NO_MITS_FLAGS}")

# These are the files we want to give students
install(TARGETS lab3C lab3B lab3A DESTINATION "${RELEASE_DIR}/lab03")
install(FILES lab3C.c lab3B.c lab3A.c DESTINATION "${RELEASE_DIR}/lab03")

