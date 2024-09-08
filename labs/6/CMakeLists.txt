add_executable(task6_unit tests/unit.cpp solution.cpp)

target_link_libraries(task6_unit PRIVATE gtest_main)

add_test(NAME Task6UnitTest COMMAND task6_unit)
