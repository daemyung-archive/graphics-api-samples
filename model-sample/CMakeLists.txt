# MIT License
#
# Copyright (c) 2018 DAEMYUNG, JANG
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

#
# Add triangle executable.
#
add_executable(ModelSample WIN32
	source/model-resources.h
	source/gl-model-sample.h
	source/gl-model-sample.cpp
	source/main.cpp)

#
# Link libraries
#
target_link_libraries(ModelSample
	PRIVATE
		Common
        Stb)

#
# Compile definitions
#   
target_compile_definitions(ModelSample
    PRIVATE
    	RESOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/resources")

#
# Set properties.
#
set_target_properties(ModelSample
    PROPERTIES
        CXX_STANDARD          17
		CXX_STANDARD_REQUIRED ON)

add_custom_command(TARGET ModelSample POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${PROJECT_SOURCE_DIR}/external/assimp/lib/x64/assimp-vc140-mt.dll"
    $<TARGET_FILE_DIR:ModelSample>)