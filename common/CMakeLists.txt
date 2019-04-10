#
# Add common library.
#
add_library(Common
	STATIC
		include/common/sample.h
		include/common/win32-application.h
        include/common/gl-sample.h
        include/common/vk-sample.h
        include/common/dx-sample.h
        include/common/camera.h
        include/common/model.h)

#
# Add include directories.
#
target_include_directories(Common
    PUBLIC
        include)

#
# Specify libraries to use when linking.
#
target_link_libraries(Common
	PUBLIC
        Khronos
        Assimp
        glm
        Microsoft
        ${CMAKE_DL_LIBS})

#
# Add sources to Platform on Windows.
#
target_sources(Common
	PRIVATE
        source/sample.cpp
        source/win32-application.cpp
        source/gl-sample.cpp
        source/vk-sample.cpp
        source/dx-sample.cpp
        source/camera.cpp
        source/model.cpp)

#
# Add compile definitions to Platform on Windows
#
target_compile_definitions(Common
    PUBLIC
        STRICT
        UNICODE
        NOMINMAX)

#
# Set properties.
#
set_target_properties(Common
    PROPERTIES
        CXX_STANDARD          17
        CXX_STANDARD_REQUIRED ON)