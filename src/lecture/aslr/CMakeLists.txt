cmake_minimum_required(VERSION 2.8)

# Adds an executable target
add_executable(aslr2 aslr2.c)
SET_FLAGS(aslr2 "-static -z execstack -fno-stack-protector")

add_executable(aslr_leak1 aslr_leak1.c)
SET_FLAGS(aslr_leak1 "-pie -fPIE -fno-stack-protector")

add_executable(aslr_leak2 aslr_leak2.c)
SET_FLAGS(aslr_leak2 "-pie -fPIE -fno-stack-protector")

# These are the files we want to give students
install(TARGETS aslr2 aslr_leak1 aslr_leak2 DESTINATION "${RELEASE_DIR}/aslr")
install(FILES aslr2.c aslr_leak1.c aslr_leak2.c DESTINATION "${RELEASE_DIR}/aslr")
