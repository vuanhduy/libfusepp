cmake_minimum_required(VERSION 3.17)
project(libfusepp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_FILE_OFFSET_BITS=64 -fno-omit-frame-pointer -fsanitize=address -Wunused-parameter")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g")
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake" ${CMAKE_MODULE_PATH})

find_package(FUSE REQUIRED)
find_package(GLog REQUIRED)

include_directories(${FUSE_INCLUDE_DIR})
include_directories(${GLOG_INCLUDE_DIR})
include_directories(include)

add_library(libfusepp include/FusePP.h src/FusePP.cpp)

# examples
add_executable(MyFuse examples/MyFuse.h examples/MyFuse.cpp)
target_link_libraries(MyFuse libfusepp)
target_link_libraries(MyFuse ${FUSE_LIBRARIES})
target_link_libraries(MyFuse ${GLOG_LIBRARIES})

#add_executable(MyFuseExample examples/main.cpp)
#target_link_libraries(MyFuseExample ${GLOG_LIBRARIES})
