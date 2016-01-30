cmake_minimum_required(VERSION 2.8)

project(NN-aim)

file(GLOB HEADERS NN-aim/*.h)
file(GLOB SOURCES NN-aim/*.cpp)

include_directories(NN-aim/include/SDL2)
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} SDL2)

if(WIN32)
	link_directories(NN-aim/lib/win32)
	target_link_libraries(${PROJECT_NAME} SDL2main)
else()
	add_definitions(-std=c++11)
endif()

