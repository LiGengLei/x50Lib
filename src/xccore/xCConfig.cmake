# - Config file for the project package
# In Binary dir
if(EXISTS "/home/lgl/master/SCARA/xCLib/src/xccore/CMakeCache.txt")
   include("/home/lgl/master/SCARA/xCLib/src/xccore/xCBuildTreeSettings.cmake")
else()
  set(xC_INCLUDE_DIRS "/home/lgl/master/SCARA/xCLib/src/xccore/../../../include")
endif()

# Our library dependencies (contains definitions for IMPORTED targets)
include("/home/lgl/master/SCARA/xCLib/src/xccore/xC.cmake")

# Our library path, if the package has not been installed
set(XC_LIBRARY_PATH          /home/lgl/master/SCARA/xCLib/src/xccore/lib)

# These are IMPORTED targets created
set(XC_INCLUDE_DIRS          ${xC_INCLUDE_DIRS} /usr/include)
set(XC_LIBRARIES             xC-core;/usr/lib/x86_64-linux-gnu/libboost_system.so;xC-math)
