#
# Add subdirectories to build.
#
add_library(Assimp
	INTERFACE)

#
# Add include directories.
#
target_include_directories(Assimp
	INTERFACE
		include)

#
# Link libraries
#
target_link_libraries(Assimp
	INTERFACE
		"${CMAKE_CURRENT_SOURCE_DIR}/lib/x64/assimp-vc140-mt.lib")