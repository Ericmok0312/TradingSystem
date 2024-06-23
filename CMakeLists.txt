set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
  CACHE STRING "Vcpkg toolchain file")
project(ts)
set(CMAKE_MINIMUM_REQUIRED_VERSION 3.10.0)

add_definitions(-pthread)

find_package(jsoncpp CONFIG REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/libs/spdlog-1.14.1/include)
include_directories(${PROJECT_SOURCE_DIR}/libs/nng-1.8.0/include)
include_directories(${PROJECT_SOURCE_DIR}/src)

link_directories(${PROJECT_SOURCE_DIR}/src/lib/)

file(GLOB SRC "${PROJECT_SOURCE_DIR}/src/Interface/*.cpp" "${PROJECT_SOURCE_DIR}/src/Helper/*.cpp")
add_executable(test test.cpp ${SRC})
target_link_libraries(test PRIVATE pthread)
target_link_libraries(test PRIVATE nng.a)
target_link_libraries(test PRIVATE jsoncpp::jsoncpp)