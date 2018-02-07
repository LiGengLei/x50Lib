# - Config file for the project package
# In Binary dir
if(EXISTS "/home/lgl/master/SCARA/xCLib/src/xcdev/CMakeCache.txt")
   include("/home/lgl/master/SCARA/xCLib/src/xcdev/xCDevBuildTreeSettings.cmake")
else()
  set(xCDev_INCLUDE_DIRS "/home/lgl/master/SCARA/xCLib/src/xcdev/../../../include")
endif()

# Our library dependencies (contains definitions for IMPORTED targets)
include("/home/lgl/master/SCARA/xCLib/src/xcdev/xCDev.cmake")

# Our library path, if the package has not been installed
set(XCDEV_LIBRARY_PATH                /home/lgl/master/SCARA/xCLib/src/xcdev/lib)

# These are IMPORTED targets created
set(XCDEV_INCLUDE_DIRS                ${xCDev_INCLUDE_DIRS})
set(XCDEV_LIBRARIES                   xCDev-core;-lpthread;/usr/lib/x86_64-linux-gnu/libboost_system.so;/usr/lib/x86_64-linux-gnu/libboost_thread.so;xCDev-PMAC;-lpthread;/usr/lib/x86_64-linux-gnu/libboost_system.so;/usr/lib/x86_64-linux-gnu/libboost_thread.so)
