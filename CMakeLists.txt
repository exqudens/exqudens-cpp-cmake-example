cmake_minimum_required(VERSION 3.17)
project(exqudens_cpp_cmake_example VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)

# declare library
add_library(ExqudensExample SHARED)
target_include_directories(ExqudensExample
    PRIVATE src/main/cpp
)
target_sources(ExqudensExample
    PRIVATE src/main/cpp/exqudens/example/StringUtils.hpp
            src/main/cpp/exqudens/example/StringUtils.cpp
)

# declare executable
add_executable(ExqudensExampleCPP)
target_include_directories(ExqudensExampleCPP
    PRIVATE src/main/cpp
)
target_sources(ExqudensExampleCPP
    PRIVATE src/main/cpp/main.cpp
)
target_link_libraries(ExqudensExampleCPP
    PRIVATE ExqudensExample
)

# declare test library
add_library(ExqudensExampleTest SHARED)
target_include_directories(ExqudensExampleTest
    PRIVATE src/test/cpp
            src/main/cpp
)
target_sources(ExqudensExampleTest
    PRIVATE src/test/cpp/exqudens/example/test/Runner.hpp
            src/test/cpp/exqudens/example/test/Runner.cpp
            src/test/cpp/exqudens/example/test/StringUtilsTests.hpp
            src/test/cpp/exqudens/example/test/StringUtilsTests.cpp
)
target_link_libraries(ExqudensExampleTest
    PRIVATE ExqudensExample
)

# declare test executable
add_executable(TestExqudensExampleCPP)
target_include_directories(TestExqudensExampleCPP
    PRIVATE src/test/cpp
)
target_sources(TestExqudensExampleCPP
    PRIVATE src/test/cpp/main.cpp
)
target_link_libraries(TestExqudensExampleCPP
    PRIVATE ExqudensExampleTest
)

# enable module 'CTest'
enable_testing()

# add tests
add_test("StringUtilsTests.test_1" TestExqudensExampleCPP "StringUtilsTests.test_1")
add_test("main" ExqudensExampleCPP)
