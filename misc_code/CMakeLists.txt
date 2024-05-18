
cmake_minimum_required(VERSION 3.16.3 FATAL_ERROR)
project(MY_GRAND_PROJECT)

find_package(PCL REQUIRED COMPONENTS common visualization io)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

find_package(OpenCV REQUIRED)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

add_executable(cloud_viewer cloud_viewer.cpp)
target_link_libraries(cloud_viewer ${PCL_LIBRARIES}  libpthread.so libboost_thread.so)

add_executable(depth_viewer depth_viewer.cpp)
target_link_libraries(depth_viewer ${PCL_LIBRARIES} ${OpenCV_LIBS})
