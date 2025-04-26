cmake_minimum_required(VERSION 3.15)
project(regex_search VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set build type if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Add compiler warnings
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find dependencies using Conan
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake OPTIONAL RESULT_VARIABLE CONAN_FILE_FOUND)
if(CONAN_FILE_FOUND)
    conan_basic_setup(TARGETS)
else()
    message(WARNING "Conan build info not found, dependencies must be installed manually")
endif()

# Find Boost package
find_package(Boost REQUIRED COMPONENTS regex)

# Set include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Create library target
add_library(regex_lib
    src/regex_searcher.cpp
)

# Link library with dependencies
if(TARGET CONAN_PKG::boost)
    target_link_libraries(regex_lib PUBLIC CONAN_PKG::boost)
else()
    target_link_libraries(regex_lib PUBLIC Boost::regex)
endif()

target_include_directories(regex_lib PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Create executable target
add_executable(regex_search
    src/main.cpp
)

# Link executable with our library
target_link_libraries(regex_search PRIVATE regex_lib)

# Add test executable
enable_testing()
add_executable(regex_test
    test/regex_searcher_test.cpp
)

# Link test with our library
if(TARGET CONAN_PKG::boost)
    target_link_libraries(regex_test PRIVATE regex_lib CONAN_PKG::boost)
else()
    target_link_libraries(regex_test PRIVATE regex_lib Boost::regex)
endif()

# Add test
add_test(NAME RegexSearcherTest COMMAND regex_test)

# Install targets
install(TARGETS regex_search regex_lib
    EXPORT regex_search-targets
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    INCLUDES DESTINATION include
)

# Install headers
install(FILES include/regex_searcher.hpp DESTINATION include)

# Install CMake config files
install(EXPORT regex_search-targets
    FILE regex_search-targets.cmake
    NAMESPACE regex_search::
    DESTINATION lib/cmake/regex_search
)

# Generate and install version file and package config file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/regex_search-config-version.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/regex_search-config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/regex_search-config.cmake"
    INSTALL_DESTINATION lib/cmake/regex_search
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/regex_search-config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/regex_search-config-version.cmake"
    DESTINATION lib/cmake/regex_search
)
