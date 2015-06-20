cmake_minimum_required(VERSION 2.8)

# Adds an executable target
add_executable(lab8C lab8C.c)
SET_FLAGS(lab8C "-z relro -z now -fPIE -pie -fstack-protector-all")

add_executable(lab8B lab8B.c)
SET_FLAGS(lab8B "-z relro -z now -fPIE -pie -fstack-protector-all")

add_executable(lab8A lab8A.c)
SET_FLAGS(lab8A "-static -fstack-protector-all -mpreferred-stack-boundary=2")

# These are the files we want to give students
install(TARGETS lab8C lab8B lab8A DESTINATION "${RELEASE_DIR}/lab08")
install(FILES lab8C.c lab8B.c lab8A.c lab8A.readme DESTINATION "${RELEASE_DIR}/lab08")
