cmake_minimum_required(VERSION 2.8)

# Adds an executable target
add_executable(rect rect.cpp)

add_executable(cpp_lec01 cpp_lec01.cpp)

add_executable(cpp_lec02 cpp_lec02.cpp)

# These are the files we want to give students
install(TARGETS rect cpp_lec01 cpp_lec02 DESTINATION "${RELEASE_DIR}/cpp")
install(FILES rect.cpp cpp_lec01.cpp cpp_lec02.cpp DESTINATION "${RELEASE_DIR}/cpp")
