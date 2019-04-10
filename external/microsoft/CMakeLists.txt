#
# Add subdirectories to build.
#
add_library(Microsoft
	INTERFACE)

#
# Add include directories.
#
target_include_directories(Microsoft
	INTERFACE
		include)

#
# Link libraries
#
target_link_libraries(Microsoft
	INTERFACE
		dxgi.lib
		d3dcompiler.lib
		d3d12.lib)