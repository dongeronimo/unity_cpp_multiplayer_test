cmake_minimum_required(VERSION 3.0)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake)
project(multiplayer_book)
set (libmultiplayer_destination "C:\\Users\\lucia\\programacao\\My project\\Assets\\Plugins")
find_package(fmt CONFIG REQUIRED)

file (GLOB_RECURSE dllsrc libmultiplayer/*.cpp libmultiplayer/*.h)
set (precompiledHeader libmultiplayer/RoboCatPCH.h)
add_library(libmultiplayer SHARED ${dllsrc})
if(WIN32)
	target_link_libraries(libmultiplayer PRIVATE wsock32 ws2_32)
endif()
target_link_libraries(libmultiplayer PRIVATE fmt::fmt)
target_include_directories(libmultiplayer PRIVATE libmultiplayer)
set_target_properties(libmultiplayer PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY_DEBUG ${libmultiplayer_destination}
	RUNTIME_OUTPUT_DIRECTORY_RELEASE ${libmultiplayer_destination})

add_executable(TestUdpServer ${dllsrc} TestUDPServer.cpp)
if(WIN32)
	target_link_libraries(TestUdpServer PRIVATE wsock32 ws2_32)
endif()
target_link_libraries(TestUdpServer PRIVATE fmt::fmt)
target_include_directories(TestUdpServer PRIVATE libmultiplayer)

