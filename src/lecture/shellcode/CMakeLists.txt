cmake_minimum_required(VERSION 2.8)

# Adds an executable target
add_executable(inject inject.c)
SET_FLAGS(inject "${NO_MITS_FLAGS}")

# These are the files we want to give students
install(TARGETS inject DESTINATION "${RELEASE_DIR}/shellcode")
install(FILES inject.c DESTINATION "${RELEASE_DIR}/shellcode")
