set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

message(STATUS "C++ compiler: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "C++ standard: ${CMAKE_CXX_STANDARD}")

# Включаем поддержку тестов
enable_testing()

# Подключаем FetchContent для загрузки Google Test
include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/release-1.12.1.zip
)

FetchContent_MakeAvailable(googletest)

# Включаем Google Test в тесты
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(labs)