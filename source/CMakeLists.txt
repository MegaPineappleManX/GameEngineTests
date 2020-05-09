cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(Tutorial VERSION 1.0)


# Download and unpack glfw
configure_file(CMakeLists-glfw.txt.in glfw/CMakeLists.txt)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/glfw
)
if(result)
  message(FATAL_ERROR "CMake step for glfw failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/glfw )
if(result)
  message(FATAL_ERROR "Build step for glfw failed: ${result}")
endif()

# Download and unpack glad
configure_file(CMakeLists-glad.txt.in glad/CmakeLists.txt)
set(GLAD_INSTALL ON)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/glad
)
if(result)
  message(FATAL_ERROR "CMake step for glad failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/glad )
if(result)
  message(FATAL_ERROR "Build step for glad failed: ${result}")
endif()


# need to figure out how to include dear imgui
# for now using git submodule

file(GLOB IMGUI_SOURCE imgui/*.cpp imgui/*.h imgui/examples/imgui_impl_glfw.h imgui/examples/imgui_impl_opengl3.h imgui/examples/imgui_impl_glfw.cpp imgui/examples/imgui_impl_opengl3.cpp)

file(GLOB RES_FILES *.frag *.vert *.glsl *.h)

add_executable(Tutorial ${RES_FILES} ${IMGUI_SOURCE} Main.cpp)


add_subdirectory(
    ${CMAKE_BINARY_DIR}/glfw-src
    ${CMAKE_BINARY_DIR}/glfw-build)

add_subdirectory(
    ${CMAKE_BINARY_DIR}/glad-src
    ${CMAKE_BINARY_DIR}/glad-build)

target_link_libraries(Tutorial 
  PUBLIC
  glad
  glfw


  PRIVATE
  ${CMAKE_DL_LIBS})



