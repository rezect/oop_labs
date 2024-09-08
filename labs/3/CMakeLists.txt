add_executable(task3_unit tests/unit.cpp solution.cpp)

target_link_libraries(task3_unit PRIVATE gtest_main)

add_test(NAME Task3UnitTest COMMAND task3_unit)
