add_executable(task2_unit tests/unit.cpp solution.cpp)

target_link_libraries(task2_unit PRIVATE gtest_main)

add_test(NAME Task2UnitTest COMMAND task2_unit)
