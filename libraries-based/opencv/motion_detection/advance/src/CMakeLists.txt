# cmake needs this line
cmake_minimum_required(VERSION 2.8)

# add config file
configure_file( md_config.hpp.in ${CMAKE_BINARY_DIR}/generated/md_config.hpp )

# add dir
include_directories( ${CMAKE_BINARY_DIR}/generated/ )
include_directories("include")

# Declare the executable target built from your sources
add_executable(main main.cpp)

# Link your application with OpenCV libraries
target_link_libraries(main ${OpenCV_LIBS})
