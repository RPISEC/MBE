cmake_minimum_required(VERSION 2.8)

# Adds an executable target
add_executable(canary canary.c)
add_executable(heap heap.c)
add_executable(uninitialized_data uninitialized_data.c)

# These are the files we want to give students
install(TARGETS canary heap uninitialized_data DESTINATION "${RELEASE_DIR}/misc")
install(FILES canary.c heap.c uninitialized_data.c DESTINATION "${RELEASE_DIR}/misc")
