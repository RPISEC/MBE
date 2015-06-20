cmake_minimum_required(VERSION 2.8)

# Adds an executable target
add_executable(heap_chunks heap_chunks.c)

add_executable(heap_smash heap_smash.c)

add_executable(heap_uaf heap_uaf.c)
SET_FLAGS(heap_uaf "-z relro -z now -fPIE -pie -fstack-protector-all")

add_executable(sizes sizes.c)

# These are the files we want to give students
install(TARGETS heap_chunks heap_smash heap_uaf sizes DESTINATION "${RELEASE_DIR}/heap")
install(FILES heap_chunks.c heap_smash.c heap_uaf.c sizes.c DESTINATION "${RELEASE_DIR}/heap")
