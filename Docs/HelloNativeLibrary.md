# Native Library Hello World

## 1) Create the cmake project:
```
cmake_minimum_required(VERSION 3.0)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake)
project(multiplayer_book)

file (GLOB_RECURSE dllsrc libmultiplayer/*.cpp libmultiplayer/*.h)

add_library(libmultiplayer SHARED ${dllsrc})
set (libmultiplayer_destination "C:\\Users\\lucia\\programacao\\My project\\Assets\\Plugins")
set_target_properties(libmultiplayer PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY_DEBUG ${libmultiplayer_destination}
	RUNTIME_OUTPUT_DIRECTORY_RELEASE ${libmultiplayer_destination})
```
```GLOB``` finds files and put them in a single list, based on path and prefix.
```add_library``` creates the library, the SHARED parameter value indicates that the library will be a dll.
```set_target_properties``` copies the built artifact to the unity's project asset folder.

## 2) The dll interface
The safest way to expose dll functionality is as C functions. That's because c++ mangles the name of c++ classes. Also, C# does not understand what is a c++ class. So C functions, primitive types, enums and POD structs are the only data that can cross the barrier:
```
int counter = 0;
extern "C" __declspec(dllexport) void __stdcall Initialize() {
    counter = 0;
}

extern "C" __declspec(dllexport) int __stdcall GetCounter() {
    return counter;
}

extern "C" __declspec(dllexport) void __stdcall Increment() {
    counter++;
}
```

## 3) Importing the functions in unity
In a MonoBehaviour:
```
    [DllImport("libmultiplayer")]
    public static extern void Initialize();
    [DllImport("libmultiplayer")]
    public static extern int GetCounter();
    [DllImport("libmultiplayer")]
    public static extern void Increment();
```
```public``` is optional. They can have any access qualifier. ```static extern``` isn't. ```DllImport``` tells which dll has the functions.