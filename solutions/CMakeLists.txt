function(solution)
    cmake_parse_arguments(SOLUTION "" "NAME" "" ${ARGN})

    string(TOUPPER ${SOLUTION_NAME} SUIT)
    string(CONCAT SUIT_TEST ${SUIT} "_SUIT")
    string(CONCAT SOLUTION_TEST_SRC ${SOLUTION_NAME} ".cpp")

    add_executable(${SOLUTION_NAME} "${SOLUTION_TEST_SRC}")
    add_test(NAME ${SUIT_TEST} COMMAND ${SOLUTION_NAME})
endfunction()

# leetcode
solution(NAME "minimum_difficulty_job_schedule")
solution(NAME "climbing_stairs")
solution(NAME "add_two_numbers")
solution(NAME "gray_code")
solution(NAME "palindrome_list")
solution(NAME "two_sum")
solution(NAME "maximum_count_pos_neg")
solution(NAME "count_neg_in_matrix")
solution(NAME "find_number_even_digits")
solution(NAME "running_sum")
solution(NAME "find_pivot_index")
solution(NAME "gcd_array")
solution(NAME "trap_rain_water")
solution(NAME "isomorphic_string")

# codewars
solution(NAME "supermarket_queue")

# other
solution(NAME "subarray_k_max_sum")
