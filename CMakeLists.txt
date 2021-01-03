cmake_minimum_required(VERSION 3.17)
project(exqudens_cpp_cmake_example VERSION 1.0.0)

# configuration --------------------------------------------------

# configuration extensions
if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/extension.cmake")
    file(
        DOWNLOAD
            "https://raw.githubusercontent.com/exqudens/exqudens-cmake/6.0.0/src/main/cmake/extension.cmake"
            "${CMAKE_CURRENT_SOURCE_DIR}/extension.cmake"
        EXPECTED_MD5
            "7fc6969f2d2d9477f7e89ebbca76bcc5"
    )
endif()
include(extension.cmake)

# dependencies targets variables
set_if_not_defined(DEPENDENCIES_MODE "QUIET") # 'QUIET' or 'REQUIRED' or 'EXACT'

# dependencies targets --------------------------------------------------

# dependencies targets extensions
include(ExternalProject)

# dependencies targets variables
set_if_not_defined(DOWNLOADS_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/downloads")
set_if_not_defined(PACKAGES_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/packages")

# (optional) dependency target 'pkg-config-lite'
ExternalProject_Add(pkg-config-lite
    DOWNLOAD_DIR      "${DOWNLOADS_PREFIX}/pkg-config-lite-0.28.1"
    DOWNLOAD_NAME     "archive.zip"
    INSTALL_DIR       "${PACKAGES_PREFIX}/pkg-config-lite-0.28.1"
    URL               "https://sourceforge.net/projects/pkgconfiglite/files/0.28-1/pkg-config-lite-0.28-1_bin-win32.zip"
    URL_MD5           "6004df17818f5a6dbf19cb335cc92702"
    EXCLUDE_FROM_ALL  TRUE
    CONFIGURE_COMMAND ""
    BUILD_COMMAND     ""
    TEST_COMMAND      ""
    INSTALL_COMMAND   ${CMAKE_COMMAND} -E copy_directory <SOURCE_DIR> <INSTALL_DIR>
)

# dependency target 'gtest-gmock'
ExternalProject_Add(gtest-gmock
    DOWNLOAD_DIR        "${DOWNLOADS_PREFIX}/gtest-gmock-1.10.0-custom"
    DOWNLOAD_NAME       "archive.zip"
    INSTALL_DIR         "${PACKAGES_PREFIX}/gtest-gmock-1.10.0-custom"
    URL                 "https://github.com/google/googletest/archive/389cb68b87193358358ae87cc56d257fd0d80189.zip"
    URL_MD5             "07166e65eed56641d582d139cd750be0"
    EXCLUDE_FROM_ALL    TRUE
    CMAKE_ARGS          "-DCMAKE_INSTALL_PREFIX=${PACKAGES_PREFIX}/gtest-gmock-1.10.0-custom"
    TEST_BEFORE_INSTALL TRUE
)

# update search path
list(APPEND CMAKE_PREFIX_PATH
    "${PACKAGES_PREFIX}/pkg-config-lite-0.28.1"
    "${PACKAGES_PREFIX}/gtest-gmock-1.10.0-custom"
)

# dependencies --------------------------------------------------

# dependency 'PkgConfig'
find_package(PkgConfig "0.28" ${DEPENDENCIES_MODE})

# dependency 'GTest'
find_package(GTest "1.10.0" ${DEPENDENCIES_MODE})

# project --------------------------------------------------

# variables
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
