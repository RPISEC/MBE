cmake_minimum_required(VERSION 2.8)

# Adds an executable target
add_executable(lab5C lab5C.c)
SET_FLAGS(lab5C "-fno-stack-protector")

add_executable(lab5B lab5B.c)
SET_FLAGS(lab5B "--static -fno-stack-protector")

add_executable(lab5A lab5A.c)
SET_FLAGS(lab5A "--static")

# These are the files we want to give students
install(TARGETS lab5C lab5B lab5A DESTINATION "${RELEASE_DIR}/lab05")
install(FILES lab5C.c lab5B.c lab5A.c DESTINATION "${RELEASE_DIR}/lab05")

