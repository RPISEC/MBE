cmake_minimum_required(VERSION 2.8)

# Adds an executable target
add_executable(fmt_lec01 fmt_lec01.c)
add_executable(fmt_lec02 fmt_lec02.c)
add_executable(fmt_lec03 fmt_lec03.c)
add_executable(fmt_lec04 fmt_lec04.c)

# These are the files we want to give students
install(TARGETS fmt_lec01 fmt_lec02 fmt_lec03 fmt_lec04 DESTINATION "${RELEASE_DIR}/format_strings")
install(FILES fmt_lec01.c fmt_lec02.c fmt_lec03.c fmt_lec04.c DESTINATION "${RELEASE_DIR}/format_strings")
