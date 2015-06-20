cmake_minimum_required(VERSION 2.8)

# Adds an executable target
add_executable(lab7C lab7C.c)
SET_FLAGS(lab7C "-z relro -z now -fPIE -pie -fstack-protector-all")

add_executable(lab7A lab7A.c)
SET_FLAGS(lab7A "-static -z relro -z now -fstack-protector-all")

# These are the files we want to give students
install(TARGETS lab7C lab7A DESTINATION "${RELEASE_DIR}/lab07")
install(FILES lab7C.c lab7A.c lab7A.readme DESTINATION "${RELEASE_DIR}/lab07")
