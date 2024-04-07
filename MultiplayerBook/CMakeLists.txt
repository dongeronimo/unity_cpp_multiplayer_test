cmake_minimum_required(VERSION 3.20)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake)

project(multiplayer_book)


set (libmultiplayer_destination "C:\\Users\\lucia\\programacao\\My project\\Assets\\Plugins")
find_package(fmt CONFIG REQUIRED)


file (GLOB_RECURSE dllsrc libmultiplayer/*.cpp libmultiplayer/*.h)
set (precompiledHeader libmultiplayer/RoboCatPCH.h)
add_library(libmultiplayer SHARED ${dllsrc})
#Versão shared da dll, pra unity
if(WIN32)
	target_link_libraries(libmultiplayer PRIVATE wsock32 ws2_32)
endif()
target_link_libraries(libmultiplayer PRIVATE fmt::fmt)
target_include_directories(libmultiplayer PRIVATE libmultiplayer)
set_target_properties(libmultiplayer PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY_DEBUG ${libmultiplayer_destination}
	RUNTIME_OUTPUT_DIRECTORY_RELEASE ${libmultiplayer_destination})
#Versão static pra testes
add_library(libmultiplayerstatic STATIC ${dllsrc})
if(WIN32)
	target_link_libraries(libmultiplayerstatic PRIVATE wsock32 ws2_32)
endif()
target_link_libraries(libmultiplayerstatic PRIVATE fmt::fmt)
target_include_directories(libmultiplayerstatic PRIVATE libmultiplayer)

#Teste de criação de um servidor simplezinho
add_executable(TestUdpServer ${dllsrc} TestUDPServer.cpp)
if(WIN32)
	target_link_libraries(TestUdpServer PRIVATE wsock32 ws2_32)
endif()
target_link_libraries(TestUdpServer PRIVATE fmt::fmt)
target_include_directories(TestUdpServer PRIVATE libmultiplayer)

#Demo de serialização, testa hosts se conectarem e trocarem dados de um mundo
add_executable(SerializationDemoServer 
	serializationTest/SerializationCommon.h
	serializationTest/SerializationDemoServer.cpp
)
target_link_libraries(SerializationDemoServer 
	PRIVATE 
	fmt::fmt libmultiplayerstatic
)
target_include_directories(SerializationDemoServer PRIVATE libmultiplayer)
add_executable(SerializationDemoClient 
	serializationTest/SerializationCommon.h
	serializationTest/SerializationDemoClient.cpp
)
target_link_libraries(SerializationDemoClient 
	PRIVATE 
	fmt::fmt libmultiplayerstatic
	"C:\\Users\\lucia\\programacao\\My project\\MultiplayerBook\\PDCursesMod-master-build\\wincon\\Debug\\pdcursesstaticd.lib"
	)
target_include_directories(SerializationDemoClient PRIVATE 
	libmultiplayer
	PDCursesMod-master
)
