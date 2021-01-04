cmake_minimum_required(VERSION 3.17)
project(exqudens_cpp_cmake_example VERSION 1.0.0)

######################################################################
# configuration ######################################################
######################################################################

# extensions
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

# configuration variables
set_if_not_defined(MAIN_DEPENDENCIES_MODE "QUIET") # 'QUIET' or 'REQUIRED' or 'EXACT'
set_if_not_defined(TEST_DEPENDENCIES_MODE "QUIET") # 'QUIET' or 'REQUIRED' or 'EXACT'

######################################################################
# install dependency targets #########################################
######################################################################

# extensions
include(ExternalProject)

# variables
set_if_not_defined(DOWNLOADS_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/downloads")
set_if_not_defined(PACKAGES_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/packages")

# main ------------------------------

# (main) install dependency target 'pkg-config-lite'
ExternalProject_Add(install-pkg-config-lite
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

# (main) install dependency target 'zlib'
ExternalProject_Add(install-zlib
    DOWNLOAD_DIR        "${DOWNLOADS_PREFIX}/zlib-1.2.11"
    DOWNLOAD_NAME       "archive.zip"
    INSTALL_DIR         "${PACKAGES_PREFIX}/zlib-1.2.11"
    URL                 "https://github.com/madler/zlib/archive/v1.2.11.zip"
    URL_MD5             "9d6a627693163bbbf3f26403a3a0b0b1"
    EXCLUDE_FROM_ALL    TRUE
    TEST_BEFORE_INSTALL TRUE
    CMAKE_ARGS
        "-DCMAKE_PREFIX_PATH=${PACKAGES_PREFIX}/pkg-config-lite-0.28.1"
        "-DCMAKE_INSTALL_PREFIX=${PACKAGES_PREFIX}/zlib-1.2.11"
)

# (main) install dependency target 'libpng'
ExternalProject_Add(install-libpng
    DOWNLOAD_DIR     "${DOWNLOADS_PREFIX}/libpng-1.6.35"
    DOWNLOAD_NAME    "archive.zip"
    INSTALL_DIR      "${PACKAGES_PREFIX}/libpng-1.6.35"
    URL              "https://github.com/glennrp/libpng/archive/v1.6.35.zip"
    URL_MD5          "160403f7a8784c300bc75f5e16cecaef"
    EXCLUDE_FROM_ALL TRUE
    TEST_COMMAND     ""
    LIST_SEPARATOR   <sep>
    CMAKE_ARGS
        "-DCMAKE_PREFIX_PATH=${PACKAGES_PREFIX}/pkg-config-lite-0.28.1<sep>${PACKAGES_PREFIX}/zlib-1.2.11"
        "-DCMAKE_INSTALL_PREFIX=${PACKAGES_PREFIX}/libpng-1.6.35"
)

# (main) install dependency target 'pngwriter'
ExternalProject_Add(install-pngwriter
    DOWNLOAD_DIR     "${DOWNLOADS_PREFIX}/pngwriter-0.7.0"
    DOWNLOAD_NAME    "archive.zip"
    INSTALL_DIR      "${PACKAGES_PREFIX}/pngwriter-0.7.0"
    URL              "https://github.com/pngwriter/pngwriter/archive/0.7.0.zip"
    URL_MD5          "fd9fc5a6c80052c1123d2618c2187cbd"
    EXCLUDE_FROM_ALL TRUE
    TEST_COMMAND     ""
    LIST_SEPARATOR   <sep>
    CMAKE_ARGS
        "-DCMAKE_PREFIX_PATH=${PACKAGES_PREFIX}/pkg-config-lite-0.28.1<sep>${PACKAGES_PREFIX}/zlib-1.2.11<sep>${PACKAGES_PREFIX}/libpng-1.6.35"
        "-DCMAKE_INSTALL_PREFIX=${PACKAGES_PREFIX}/pngwriter-0.7.0"
)

# test ------------------------------

# (test) install dependency target 'gtest-gmock'
ExternalProject_Add(install-gtest-gmock
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
    "${PACKAGES_PREFIX}/zlib-1.2.11"
    "${PACKAGES_PREFIX}/libpng-1.6.35"
    "${PACKAGES_PREFIX}/pngwriter-0.7.0"
    "${PACKAGES_PREFIX}/gtest-gmock-1.10.0-custom"
)

######################################################################
# main ###############################################################
######################################################################

# variables
set(CMAKE_CXX_STANDARD 20)

# dependencies ------------------------------

# dependency 'PkgConfig'
find_package(PkgConfig "0.28" ${MAIN_DEPENDENCIES_MODE})

# dependency 'ZLIB'
find_package(ZLIB "1.2.11" ${MAIN_DEPENDENCIES_MODE})

# dependency 'PNG'
find_package(PNG "1.6.35" ${MAIN_DEPENDENCIES_MODE})

# dependency 'PNGwriter'
find_package(PNGwriter "0.7.0" ${MAIN_DEPENDENCIES_MODE})

# complete configuration if dependency not found
if(
    NOT PkgConfig_FOUND
    OR NOT ZLIB_FOUND
    OR NOT PNG_FOUND
    OR NOT PNGwriter_FOUND
)
    message(STATUS "Some test dependency not found: SKIP MAIN TARGETS")
    return()
endif()

# libraries ------------------------------

# declare library
add_library(ExqudensExample SHARED)
target_include_directories(ExqudensExample
    PRIVATE src/main/cpp
)
target_sources(ExqudensExample
    PRIVATE src/main/cpp/exqudens/example/StringUtils.hpp
            src/main/cpp/exqudens/example/StringUtils.cpp
)

# executables ------------------------------

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

######################################################################
# test ###############################################################
######################################################################

# dependencies ------------------------------

# dependency 'GTest'
find_package(GTest "1.10.0" ${TEST_DEPENDENCIES_MODE})

# complete configuration if dependency not found
if(NOT GTest_FOUND)
    message(STATUS "Some test dependency not found: SKIP TEST TARGETS")
    return()
endif()

# libraries ------------------------------

# declare test library
add_library(ExqudensExampleTest SHARED)
target_include_directories(ExqudensExampleTest
    PRIVATE src/test/cpp
            src/main/cpp
)
target_sources(ExqudensExampleTest
    PRIVATE src/test/cpp/exqudens/example/test/Runner.hpp
            src/test/cpp/exqudens/example/test/Runner.cpp
            src/test/cpp/exqudens/example/test/StringUtilsTestSuite.hpp
)
target_link_libraries(ExqudensExampleTest
    PRIVATE GTest::GTest
            GTest::Main
            ExqudensExample
)

# executables ------------------------------

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
add_test("StringUtilsTestSuite.test_1" TestExqudensExampleCPP "--gtest_filter=StringUtilsTestSuite.test_1")
add_test("StringUtilsTestSuite.test_2" TestExqudensExampleCPP "--gtest_filter=StringUtilsTestSuite.test_2")
add_test("main" ExqudensExampleCPP)
