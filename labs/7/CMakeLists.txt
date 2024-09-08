add_executable(task7_unit tests/unit.cpp solution.cpp)

target_link_libraries(task7_unit PRIVATE gtest_main)

add_test(NAME Task7UnitTest COMMAND task7_unit)
