cmake_minimum_required(VERSION 3.10)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Set the project name
project(RZMLTests)

enable_testing()

file(GLOB TEST_SOURCES "test/*.cpp")
file(GLOB RZML_HEADERS "include/rzml/*.h")
file(GLOB RZML_SOURCES "source/*.cpp")

add_executable(rzml_tests ${TEST_SOURCES} ${RZML_HEADERS} ${RZML_SOURCES})

target_link_libraries(
    rzml_tests
    GTest::gtest_main
)

target_include_directories(
    rzml_tests
    PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/3rdparty/glm
)

include(GoogleTest)
gtest_discover_tests(rzml_tests)


