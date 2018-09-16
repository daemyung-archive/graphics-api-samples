#
# Set the minimum requred version of cmake.
#
cmake_minimum_required(VERSION 3.1.3)

#
# Set project details.
#
project(graphics-api-samples
        VERSION   0.0.1
        LANGUAGES CXX)

#
# Add subdirectories to build.
#
add_subdirectory(external)
add_subdirectory(common)
add_subdirectory(triangle-sample)
add_subdirectory(texture-sample)
add_subdirectory(constant-sample)
add_subdirectory(camera-sample)
add_subdirectory(model-sample)