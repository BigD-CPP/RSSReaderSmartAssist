cmake_minimum_required(VERSION 3.10)

project(RSSReaderSmartAssist)

set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "" FORCE)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

add_executable(RSSReaderSmartAssist src/main.cpp src/RSSreader.cpp src/Constant.cpp)
find_package(CURL REQUIRED)
find_package(tinyxml2 CONFIG REQUIRED)

target_include_directories(RSSReaderSmartAssist PRIVATE 
	${CURL_INCLUDE_DIRS}
	${tinyxml2_INCLUDE_DIRS}
)

target_link_libraries(RSSReaderSmartAssist PRIVATE
	${CURL_LIBRARIES}
	${tinyxml2_LIBRARIES}
	tinyxml2::tinyxml2
)
