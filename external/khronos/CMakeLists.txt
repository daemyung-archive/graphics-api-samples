find_package(OpenGL REQUIRED)
find_package(Vulkan REQUIRED)

#
# Add subdirectories to build.
#
add_library(Khronos
	INTERFACE)

#
# Add include directories.
#
target_include_directories(Khronos
	INTERFACE
		include
		${OPENGL_INCLUDE_DIRS}
		${Vulkan_INCLUDE_DIRS})

#
# Set compile definitions
#
target_compile_definitions(Khronos
	INTERFACE
		VK_USE_PLATFORM_WIN32_KHR)

#
# Link libraries
#
target_link_libraries(Khronos
	INTERFACE
		${OPENGL_LIBRARIES}
		${Vulkan_LIBRARIES})