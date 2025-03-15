# CMakeList.txt : CMake project for RSSReaderSmartAssist, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")

#name of project : RSSReaderSmartAssist
project ("RSSReaderSmartAssist")
message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
message(STATUS "PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")
message(STATUS "PROJECT_BINARY_DIR: ${PROJECT_BINARY_DIR}")

add_subdirectory(external/curl)

# Add source to this project's executable.
add_executable(RSSReaderSmartAssist ${SRC_DIR}/RSSReaderSmartAssist.cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(RSSReaderSmartAssist VERSION 1.0)

#create version file 
configure_file(
	${SRC_DIR}/RSSReaderSmartAssistConfig.in 
	${PROJECT_BINARY_DIR}/RSSReaderSmartAssistConfig
)

target_link_libraries(RSSReaderSmartAssist curl)
target_include_directories(RSSReaderSmartAssist PRIVATE 
	${CURL_INCLUDE_DIRS}
	${PROJECT_BINARY_DIR}	
)