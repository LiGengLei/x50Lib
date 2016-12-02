cmake_minimum_required(VERSION 2.8)
project("xCExample")
set(CMAKE_BUILD_TYPE DEBUG)

# Packages
find_package(xC REQUIRED)
find_package(YARP REQUIRED)

# Add Include Directories
include_directories(${XC_INCLUDE_DIRS})

# Get Files
file (GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

foreach(SOURCE_FILE ${SOURCE_FILES})
  get_filename_component(EXE_NAME ${SOURCE_FILE} NAME_WE)
  add_executable(${EXE_NAME} ${SOURCE_FILE})
  target_link_libraries(${EXE_NAME} ${XC_CORE_LIBRARIES})
  target_link_libraries(${EXE_NAME} ${YARP_LIBRARIES})
endforeach(SOURCE_FILE ${SOURCE_FILES})
