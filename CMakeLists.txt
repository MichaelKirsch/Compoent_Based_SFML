cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 17)
set(PROJECT_NAME test)
project(${PROJECT_NAME})
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "${CMAKE_CURRENT_LIST_DIR}/libs/SFML-2.5.1/lib/cmake/SFML")
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.hpp") #glob all the source files intp one place
file(COPY libs/SFML-2.5.1/bin/openal32.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY "data"  DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

include_directories(src/Components)
include_directories(src/BaseClasses)
include_directories(src/Engine)
include_directories(libs/json)
include_directories(src/Entities)
include_directories(src)

add_executable(${PROJECT_NAME} ${SOURCES})

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio REQUIRED)
find_package(OpenGL REQUIRED)

target_link_libraries(${PROJECT_NAME} sfml-audio sfml-graphics sfml-window sfml-system sfml-network ${OPENGL_LIBRARIES})