cmake_minimum_required(VERSION 2.8)
include(cmake/functions.cmake)
set(CMAKE_CONFIGURATION_TYPES "Release")

# Define project settings
project(AbvanceMotionDetection)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

# Define user's options
option(Use_OpenCL "Use OpenCL" 0)
option(Show_Windows "Use imshow function" 0)
convert2number(Use_OpenCL)   # convert from ON/OFF to 1/0
convert2number(Show_Windows) # convert from ON/OFF to 1/0

# Find 3rd party library
set(OpenCV_DIR "C:/Users/jason/Downloads/opencv3/build_custom/win-install")

find_package(OpenCV REQUIRED)

# Add dir
include_directories(${BOOST_INCLUDEDIR})
link_directories(${BOOST_LIBRARYDIR})
add_subdirectory("src")

# Print summary
message(STATUS "OpenCV version: ${OpenCV_VERSION}")
message(STATUS "Executable output: ${EXECUTABLE_OUTPUT_PATH}")
