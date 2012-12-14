cmake_minimum_required(VERSION 2.6)
project(JOSEPH_CALC)

set(CMAKE_C_FLAGS "-Wall -O0 -g3")

	set(INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_BINARY_DIR})
	include_directories(${INCLUDE_DIRS})

	find_library(READLINE_LIBRARY NAMES readline)

	link_directories(${READLINE_INCLUDE_DIR})

add_executable(JOSEPH_CALC
	src/print.c
#	src/check.c
#	src/i_calculate.c
#	src/f_calculate.c
#	src/eval.c
#	src/parse.c
	src/tokenize.c
	src/main.c
	include/main.h
	)

	target_link_libraries(JOSEPH_CALC readline)
