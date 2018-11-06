
add_library(Stb
	INTERFACE)

target_include_directories(Stb
	INTERFACE
		include)

target_compile_definitions(Stb
	INTERFACE
		STB_IMAGE_IMPLEMENTATION)