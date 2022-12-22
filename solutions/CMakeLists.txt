function(solution)
	cmake_parse_arguments(SOLUTION "" "NAME" "" ${ARGN})

	string(TOUPPER ${SOLUTION_NAME} SUIT)
	string(CONCAT SUIT_TEST ${SUIT} "_SUIT")
	string(CONCAT SOLUTION_TEST_SRC ${SOLUTION_NAME} ".cpp")

	add_executable(${SOLUTION_NAME} "${SOLUTION_TEST_SRC}")
	add_test(NAME ${SUIT_TEST} COMMAND ${SOLUTION_NAME})
endfunction()

solution(NAME "minimum_difficulty_job_schedule")
solution(NAME "climbing_stairs")
