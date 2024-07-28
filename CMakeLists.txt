set(CMAKE_TOOLCHAIN_FILE "./home/emk/vcpkg/scripts/buildsystems/vcpkg.cmake"
  CACHE STRING "Vcpkg toolchain file")


if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  set(BUILD_FOR_WIN TRUE)
endif()

option(STATIC_BUILD "Build a static binary." ${BUILD_FOR_WIN})

if(STATIC_BUILD)
  set(CMAKE_EXE_LINKER_FLAGS "-static")
  set(CMAKE_FIND_LIBRARY_SUFFIXES ".a" CONFIG)
  set(BUILD_SHARED_LIBS OFF)
endif()



project(ts)
cmake_minimum_required(VERSION 3.22)
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  set(CMAKE_GENERATOR_PLATFORM "windows")
else()
  set(CMAKE_GENERATOR_PLATFORM "x64-linux")
endif()


add_definitions(-pthread)
include(/home/emk/vcpkg/scripts/buildsystems/vcpkg.cmake)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fsanitize=address")

find_package(jsoncpp REQUIRED)


include_directories(${PROJECT_SOURCE_DIR}/libs/spdlog-1.14.1/include)
include_directories(${PROJECT_SOURCE_DIR}/libs/nng-1.8.0/include)
include_directories(${PROJECT_SOURCE_DIR}/libs/futu/include)
include_directories(${PROJECT_SOURCE_DIR}/libs/rapidjson/include)
include_directories(${PROJECT_SOURCE_DIR}/libs/lmdb)
include_directories(${PROJECT_SOURCE_DIR}/libs)
include_directories(${PROJECT_SOURCE_DIR}/src)

link_directories(${PROJECT_SOURCE_DIR}/src/lib/)

file(GLOB SRC "${PROJECT_SOURCE_DIR}/src/Interface/*.cpp" "${PROJECT_SOURCE_DIR}/src/Helper/*.cpp" "${PROJECT_SOURCE_DIR}/src/Helper/*.hpp" "${PROJECT_SOURCE_DIR}/src/FUTU/*.cpp" "${PROJECT_SOURCE_DIR}/src/DataManager/*.cpp")
add_executable(test.exe main.cpp ${SRC})

target_link_libraries(test.exe PRIVATE pthread)
target_link_libraries(test.exe PRIVATE nng.a)
target_link_libraries(test.exe PRIVATE FTAPI.a)
target_link_libraries(test.exe PRIVATE FTAPIChannel.so)
target_link_libraries(test.exe PRIVATE protobuf.a)
target_link_libraries(test.exe PRIVATE JsonCpp::JsonCpp)
target_link_libraries(test.exe PRIVATE lmdb.a)
target_link_libraries(test.exe PRIVATE boost_filesystem.a)
target_link_libraries(test.exe PRIVATE boost_thread.a)
target_link_libraries(test.exe PRIVATE boost_chrono.a)