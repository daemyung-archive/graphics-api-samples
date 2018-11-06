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
add_subdirectory(coordination-sample)
add_subdirectory(camera-sample)
add_subdirectory(model-sample)