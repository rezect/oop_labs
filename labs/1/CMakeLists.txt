add_executable(task1_unit tests/unit.cpp solution.cpp)

target_link_libraries(task1_unit PRIVATE gtest_main)

add_test(NAME Task1UnitTest COMMAND task1_unit)
