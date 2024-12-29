cmake_minimum_required(VERSION 3.4)
project(bno055)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Python
find_package(Python 3 REQUIRED COMPONENTS Interpreter Development)

# Find pybind11
find_package(pybind11 REQUIRED)

# Add the C source files
set(BNO055_SOURCES
    i2c_bno055.c
    getbno055.c
    bno055_wrapper.cpp
    bno055_binding.cpp
)

# Create the pybind11 module
pybind11_add_module(bno055 ${BNO055_SOURCES})

# Add include directories
target_include_directories(bno055 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Link against required libraries
target_link_libraries(bno055 PRIVATE i2c)

# Install the module into the Python site-packages directory
install(TARGETS bno055
        LIBRARY DESTINATION ${Python_SITELIB}
        RUNTIME DESTINATION ${Python_SITELIB})
