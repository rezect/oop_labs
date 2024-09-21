add_executable(task5_unit tests/unit.cpp)

target_link_libraries(task5_unit PRIVATE gtest_main)

add_test(NAME Task5UnitTest COMMAND task5_unit)
