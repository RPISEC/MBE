cmake_minimum_required(VERSION 2.8)

# Adds an executable target
add_executable(lab6C lab6C.c)
SET_FLAGS(lab6C "-pie -fPIE -fno-stack-protector")

add_executable(lab6B lab6B.c)
SET_FLAGS(lab6B "-z relro -z now -pie -fPIE -fno-stack-protector")

add_executable(lab6A lab6A.c)
SET_FLAGS(lab6A "-pie -fPIE -fno-stack-protector")

# These are the files we want to give students
install(TARGETS lab6C lab6B lab6A DESTINATION "${RELEASE_DIR}/lab06")
install(FILES lab6C.c lab6B.c lab6B.readme lab6A.c DESTINATION "${RELEASE_DIR}/lab06")
