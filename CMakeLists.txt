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
set_if_not_defined(DOWNLOADS_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/downloads")
set_if_not_defined(PACKAGES_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/packages")
set_if_not_defined(MAIN_DEPENDENCIES_MODE "QUIET") # 'QUIET' or 'REQUIRED' or 'EXACT'
set_if_not_defined(TEST_DEPENDENCIES_MODE "QUIET") # 'QUIET' or 'REQUIRED' or 'EXACT'
set_if_not_defined(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
set_if_not_defined(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
set_if_not_defined(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
set_if_not_defined(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
set_if_not_defined(RESOURCES_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/resources)

unset(CMAKE_SHARED_LIBRARY_PREFIX)

######################################################################
# install dependency targets #########################################
######################################################################

# extensions
include(ExternalProject)

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
        "-DCMAKE_MAKE_PROGRAM=${CMAKE_MAKE_PROGRAM}"
        "-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}"
        "-DCMAKE_WINDOWS_EXPORT_ALL_SYMBOLS=${CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS}"
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
        "-DCMAKE_MAKE_PROGRAM=${CMAKE_MAKE_PROGRAM}"
        "-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}"
        "-DCMAKE_WINDOWS_EXPORT_ALL_SYMBOLS=${CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS}"
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
        "-DCMAKE_MAKE_PROGRAM=${CMAKE_MAKE_PROGRAM}"
        "-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}"
        "-DCMAKE_WINDOWS_EXPORT_ALL_SYMBOLS=${CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS}"
        "-DBUILD_STATIC_LIBS=ON"
        "-DBUILD_SHARED_LIBS=ON"
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
    TEST_BEFORE_INSTALL TRUE
    CMAKE_ARGS
        "-DCMAKE_MAKE_PROGRAM=${CMAKE_MAKE_PROGRAM}"
        "-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}"
        "-DCMAKE_WINDOWS_EXPORT_ALL_SYMBOLS=${CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS}"
        "-DBUILD_STATIC_LIBS=ON"
        "-DBUILD_SHARED_LIBS=ON"
        "-DCMAKE_INSTALL_PREFIX=${PACKAGES_PREFIX}/gtest-gmock-1.10.0-custom"
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
# runtime-binaries ###################################################
######################################################################

# variables
get_filename_component(CXX_COMPILER_DIR ${CMAKE_CXX_COMPILER} DIRECTORY)
find_file(LIB_STDCPP     NAMES "libstdc++-6.dll"                    PATHS ${CXX_COMPILER_DIR}                              NO_DEFAULT_PATH)
find_file(LIB_GCC        NAMES "libgcc_s_dw2-1.dll"                 PATHS ${CXX_COMPILER_DIR}                              NO_DEFAULT_PATH)
find_file(LIB_ZLIB       NAMES "zlib.dll" "libzlib.dll"             PATHS ${PACKAGES_PREFIX}/zlib-1.2.11/bin               NO_DEFAULT_PATH)
find_file(LIB_PNG        NAMES "png16.dll" "libpng16.dll"           PATHS ${PACKAGES_PREFIX}/libpng-1.6.35/bin             NO_DEFAULT_PATH)
find_file(LIB_PNG_WRITER NAMES "PNGWriter.dll" "libPNGWriter.dll"   PATHS ${PACKAGES_PREFIX}/pngwriter-0.7.0/bin           NO_DEFAULT_PATH)
find_file(LIB_GTEST      NAMES "gtest.dll" "libgtest.dll"           PATHS ${PACKAGES_PREFIX}/gtest-gmock-1.10.0-custom/bin NO_DEFAULT_PATH)
find_file(LIB_GTEST_MAIN NAMES "gtest_main.dll" "libgtest_main.dll" PATHS ${PACKAGES_PREFIX}/gtest-gmock-1.10.0-custom/bin NO_DEFAULT_PATH)

set(COPY_LIB_STDCPP_COMMAND     "-E" "echo" ${LIB_STDCPP})
set(COPY_LIB_GCC_COMMAND        "-E" "echo" ${LIB_GCC})
set(COPY_LIB_ZLIB_COMMAND       "-E" "echo" ${LIB_ZLIB})
set(COPY_LIB_PNG_COMMAND        "-E" "echo" ${LIB_PNG})
set(COPY_LIB_PNG_WRITER_COMMAND "-E" "echo" ${LIB_PNG_WRITER})
set(COPY_LIB_GTEST_COMMAND      "-E" "echo" ${LIB_GTEST})
set(COPY_LIB_GTEST_MAIN_COMMAND "-E" "echo" ${LIB_GTEST_MAIN})

if(EXISTS ${LIB_STDCPP})
    set(COPY_LIB_STDCPP_COMMAND "-E" "copy" "${LIB_STDCPP}" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif()
if(EXISTS ${LIB_GCC})
    set(COPY_LIB_GCC_COMMAND "-E" "copy" "${LIB_GCC}" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif()
if(EXISTS ${LIB_ZLIB})
    set(COPY_LIB_ZLIB_COMMAND "-E" "copy" "${LIB_ZLIB}" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif()
if(EXISTS ${LIB_PNG})
    set(COPY_LIB_PNG_COMMAND "-E" "copy" "${LIB_PNG}" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif()
if(EXISTS ${LIB_PNG_WRITER})
    set(COPY_LIB_PNG_WRITER_COMMAND "-E" "copy" "${LIB_PNG_WRITER}" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif()
if(EXISTS ${LIB_GTEST})
    set(COPY_LIB_GTEST_COMMAND "-E" "copy" "${LIB_GTEST}" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif()
if(EXISTS ${LIB_GTEST_MAIN})
    set(COPY_LIB_GTEST_MAIN_COMMAND "-E" "copy" "${LIB_GTEST_MAIN}" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif()

# target
add_custom_target(copy-runtime-binaries
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/src/test/resources ${RESOURCES_OUTPUT_DIRECTORY}
    COMMAND ${CMAKE_COMMAND} ${COPY_LIB_STDCPP_COMMAND}
    COMMAND ${CMAKE_COMMAND} ${COPY_LIB_GCC_COMMAND}
    COMMAND ${CMAKE_COMMAND} ${COPY_LIB_ZLIB_COMMAND}
    COMMAND ${CMAKE_COMMAND} ${COPY_LIB_PNG_COMMAND}
    COMMAND ${CMAKE_COMMAND} ${COPY_LIB_PNG_WRITER_COMMAND}
    COMMAND ${CMAKE_COMMAND} ${COPY_LIB_GTEST_COMMAND}
    COMMAND ${CMAKE_COMMAND} ${COPY_LIB_GTEST_MAIN_COMMAND}
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
    message(STATUS "Some 'main' dependency not found: COMPLETE CONFIGURATION !!!")
    message(STATUS "PkgConfig_FOUND: ${PkgConfig_FOUND}")
    message(STATUS "ZLIB_FOUND: ${ZLIB_FOUND}")
    message(STATUS "PNG_FOUND: ${PNG_FOUND}")
    message(STATUS "PNGwriter_FOUND: ${PNGwriter_FOUND}")
    return()
endif()

# libraries ------------------------------

# declare object library
add_library(ExqudensExample OBJECT)
target_include_directories(ExqudensExample
    PRIVATE src/main/cpp
)
target_sources(ExqudensExample
    PRIVATE src/main/cpp/exqudens/util/StringUtils.hpp
            src/main/cpp/exqudens/util/StringUtils.cpp
            src/main/cpp/exqudens/util/ImageUtils.hpp
            src/main/cpp/exqudens/util/ImageUtils.cpp
)
target_link_libraries(ExqudensExample
    PRIVATE PNGwriter::PNGwriter
)

# declare static and shared library from the same object files
add_library(ExqudensExampleShared SHARED $<TARGET_OBJECTS:ExqudensExample>)
target_link_libraries(ExqudensExampleShared
    PRIVATE PNGwriter::PNGwriter
)
add_library(ExqudensExampleStatic STATIC $<TARGET_OBJECTS:ExqudensExample>)
target_link_libraries(ExqudensExampleStatic
    PRIVATE PNGwriter::PNGwriter
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
    PRIVATE ExqudensExampleShared
)
add_dependencies(ExqudensExampleCPP copy-runtime-binaries)

######################################################################
# test ###############################################################
######################################################################

# dependencies ------------------------------

# dependency 'GTest'
find_package(GTest "1.10.0" ${TEST_DEPENDENCIES_MODE} CONFIG)

# complete configuration if dependency not found
if(NOT GTest_FOUND)
    message(STATUS "Some 'test' dependency not found: COMPLETE CONFIGURATION !!!")
    message(STATUS "GTest_FOUND: ${GTest_FOUND}")
    return()
endif()

# libraries ------------------------------

# declare test library
add_library(ExqudensExampleTest OBJECT)
target_include_directories(ExqudensExampleTest
    PRIVATE src/test/cpp
            src/main/cpp
)
target_sources(ExqudensExampleTest
    PRIVATE src/test/cpp/exqudens/test/Runner.hpp
            src/test/cpp/exqudens/test/Runner.cpp
            src/test/cpp/exqudens/test/Config.hpp
            src/test/cpp/exqudens/test/Config.cpp
            src/test/cpp/exqudens/util/StringUtilsTestSuite.hpp
            src/test/cpp/exqudens/util/ImageUtilsTestSuite.hpp
)
target_link_libraries(ExqudensExampleTest
    PRIVATE GTest::gtest
            GTest::gtest_main
            ExqudensExample
)

# declare test static and shared library from the same object files
add_library(ExqudensExampleTestShared SHARED $<TARGET_OBJECTS:ExqudensExampleTest>)
target_link_libraries(ExqudensExampleTestShared
    PRIVATE ExqudensExampleShared
            GTest::gtest
            GTest::gtest_main
)
add_library(ExqudensExampleTestStatic STATIC $<TARGET_OBJECTS:ExqudensExampleTest>)
target_link_libraries(ExqudensExampleTestStatic
    PRIVATE ExqudensExampleStatic
            GTest::gtest
            GTest::gtest_main
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
    PRIVATE ExqudensExampleTestShared
)
add_dependencies(TestExqudensExampleCPP copy-runtime-binaries)

# tests ------------------------------

# enable module 'CTest'
enable_testing()

# add tests
add_test(
    NAME StringUtilsTestSuite.test1
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    COMMAND TestExqudensExampleCPP --gtest_filter=StringUtilsTestSuite.test1
)
set_tests_properties(StringUtilsTestSuite.test1 PROPERTIES ENVIRONMENT PATH=${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_test(
    NAME StringUtilsTestSuite.all
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    COMMAND TestExqudensExampleCPP --gtest_filter=StringUtilsTestSuite.*
)
set_tests_properties(StringUtilsTestSuite.all PROPERTIES ENVIRONMENT PATH=${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_test(
    NAME ImageUtilsTestSuite.all
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    COMMAND TestExqudensExampleCPP --gtest_filter=ImageUtilsTestSuite.*
)
set_tests_properties(ImageUtilsTestSuite.all PROPERTIES ENVIRONMENT PATH=${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_test(
    NAME main.parentPath
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    COMMAND ExqudensExampleCPP --parent-path
)
set_tests_properties(main.parentPath PROPERTIES ENVIRONMENT PATH=${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_test(
    NAME main.trim
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    COMMAND ExqudensExampleCPP --trim
)
set_tests_properties(main.trim PROPERTIES ENVIRONMENT PATH=${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_test(
    NAME main.readPng
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    COMMAND ExqudensExampleCPP --read-png
)
set_tests_properties(main.readPng PROPERTIES ENVIRONMENT PATH=${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
