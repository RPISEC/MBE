cmake_minimum_required(VERSION 2.8)

# Adds an executable target
add_executable(rop_exit rop_exit.c)
SET_FLAGS(rop_exit "${DISABLE_CANARY_FLAG}")

add_executable(rop_pivot rop_pivot.c)
SET_FLAGS(rop_pivot "-static")

# These are the files we want to give students
install(TARGETS rop_exit rop_pivot DESTINATION "${RELEASE_DIR}/rop")
install(FILES rop_exit.c rop_pivot.c DESTINATION "${RELEASE_DIR}/rop")
