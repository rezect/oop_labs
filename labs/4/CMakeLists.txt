add_executable(task4_unit tests/unit.cpp)

target_link_libraries(task4_unit PRIVATE gtest_main)

add_test(NAME Task4UnitTest COMMAND task4_unit)
