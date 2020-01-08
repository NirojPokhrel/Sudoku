add_library(logic_lib
                ../game_util.cpp
                ../game_solver.cpp
                ../sudoku_generator.cpp)


target_compile_options(logic_lib PRIVATE -Wall 
                -Wextra 
                -Wunused 
                -Wuninitialized 
                -Wmissing-noreturn 
                -Wunreachable-code
                -Wsign-compare 
                #-Wstrict-null-sentinel 
                -Wreturn-type 
                -Wcast-qual 
                -Wconversion
                -Wenum-compare 
                -Wsign-conversion
                -g 
                -O0)
if (CLANGTIDY)
    return()
endif()
add_executable(unittest_exec 
                game_util_test.cpp
                game_solver_test.cpp
                sudoku_generator_test.cpp)

target_link_libraries(unittest_exec ${GTEST_STATIC_LIBRARIES} pthread logic_lib)

# If gtest-library hasn't yet been built, add the dependencies for it to be installed for the 
# first time.
if (NOT GTEST_LIBRARY)
    add_dependencies(unittest_exec googletestlocal)
endif()

enable_testing()
message(STATUS "Executable - ${CMAKE_BINARY_DIR}/Classes/test/unittest_exec")
add_test(
    NAME unittest_run
    COMMAND ${CMAKE_BINARY_DIR}/Classes/test/unittest_exec 
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
