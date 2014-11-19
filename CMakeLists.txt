#cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

#project(pcd_read)

#find_package(PCL 1.2 REQUIRED)

#include_directories(${PCL_INCLUDE_DIRS})
#link_directories(${PCL_LIBRARY_DIRS})
#add_definitions(${PCL_DEFINITIONS})

#add_executable (pcd_read pcd_read.cpp)
#target_link_libraries (pcd_read ${PCL_LIBRARIES})

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

#---------------openni 
set(OPENNI_LIBRARIES openNI.lib)

#---------------opencv
#http://docs.opencv.org/trunk/doc/tutorials/introduction/linux_gcc_cmake/linux_gcc_cmake.html
set(OpenCV_DIR D:/opencv249/build)
find_package(OpenCV REQUIRED)

#---------------boost
set(BOOST_ROOT "D:/Program Files/PCL 1.6.0-x86/3rdParty/Boost")
find_package(Boost 1.49.0 REQUIRED)
message(STATUS "--BOOST_ROOT is: ${BOOST_ROOT}")
message(STATUS "--BOOST_ROOT is: ${BOOST_ROOT}")


# ---------------top level:
project(OpenniCeshi)

add_subdirectory(OpenniCeshi)
add_subdirectory(Openni_load_oni_file)
add_subdirectory(Openni_load_raw_file)

message(STATUS "version is: ${CMAKE_VERSION}")
message(STATUS "openni include dir is:$ENV{OPEN_NI_INCLUDE}")
message(STATUS "OPENNI_LIBRARIES := ${CMAKE_SOURCE_DIR}")



