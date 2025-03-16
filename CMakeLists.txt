cmake_minimum_required(VERSION 3.10)

project(RSSReaderSmartAssist CXX)

set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "" FORCE)

if(MSVC)
    add_compile_options(/std:c++20)
	message("set c++ version for MSVC")
else()
	set(CMAKE_CXX_STANDARD 20)
	set(CMAKE_CXX_STANDARD_REQUIRED True)
endif()

include_directories(include)

add_executable(RSSReaderSmartAssist src/main.cpp src/RSSreader.cpp src/Constant.cpp src/Logger.cpp src/XMLParser.cpp "include/utility/XMLParser.h")
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

find_package(CURL REQUIRED)
find_package(tinyxml2 CONFIG REQUIRED)

target_include_directories(RSSReaderSmartAssist PUBLIC 
	${CURL_INCLUDE_DIRS}
	${tinyxml2_INCLUDE_DIRS}
)

target_link_libraries(RSSReaderSmartAssist PRIVATE
	${CURL_LIBRARIES}
	${tinyxml2_LIBRARIES}
	tinyxml2::tinyxml2
)

