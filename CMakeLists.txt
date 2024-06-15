project(ts)
set(CMAKE_MINIMUM_REQUIRED_VERSION 3.10.0)

add_definitions(-std=c++11 -pthread)


include_directories(${PROJECT_SOURCE_DIR}/libs/spdlog-1.14.1/include)
include_directories(${PROJECT_SOURCE_DIR}/src)
add_executable(test test.cpp ./src/Helper/logger.cpp )
target_link_libraries(test PRIVATE pthread)


#target_link_libraries(test PRIVATE spdlog)