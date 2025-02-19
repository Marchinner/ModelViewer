# CMakeList.txt : CMake project for ModelViewer, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.29.0)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

if (MSVC)
add_compile_options(/arch:AVX2)
endif()

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")

project ("ModelViewer")

# GLFW Build Config
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

# Third Party Libraries
add_subdirectory(thirdparty/glfw-3.4)
add_subdirectory(thirdparty/glad)
add_subdirectory(thirdparty/glm-1.0.1)

# Sources
file(GLOB_RECURSE MODELVIEWER_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# Add source to this project's executable.
add_executable(ModelViewer)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ModelViewer PROPERTY CXX_STANDARD 20)
endif()

# GLFW Config
target_compile_definitions(ModelViewer PUBLIC GLFW_INCLUDE_NONE=1)

# Add all sources to project
target_sources(ModelViewer PRIVATE ${MODELVIEWER_SOURCES})

# Additional Include Path
target_include_directories(ModelViewer PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

# Additional Libraries
target_link_libraries(ModelViewer PRIVATE glm glfw glad)