cmake_minimum_required(VERSION 2.8)
project(nBody)


find_package(OpenGL REQUIRED)
#find_package(GLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIR})

file(GLOB Graphics_SOURCES Graphics/*.cpp)
file(GLOB Math_SOURCES Math/*.cpp)
file(GLOB Physics_SOURCES Physics/*.cpp)
file(GLOB Skeleton_SOURCES Skeleton/*.cpp)
file(GLOB World_SOURCES World/*.cpp)

set(main_SOURCES Environment/X11/Main.cpp)

if(WIN32)
        message(FATAL_ERROR "Sorry, WIN32 is not supported with CMake yet.")
endif(WIN32)

add_executable(nBody ${Graphics_SOURCES}
                     ${Math_SOURCES}
                     ${Physics_SOURCES}
                     ${Skeleton_SOURCES}
                     ${World_SOURCES}
                     ${main_SOURCES})

target_link_libraries(nBody ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
