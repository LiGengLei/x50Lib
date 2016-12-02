# - this module looks for Matlab
# Defines:
#  MATLAB_INCLUDE_DIRS: include path for mex.h, engine.h
#  MATLAB_LIBRARIES:   required libraries: libmex, etc
#  MATLAB_MEX_LIBRARY: path to libmex.lib
#  MATLAB_MX_LIBRARY:  path to libmx.lib
#  MATLAB_ENG_LIBRARY: path to libeng.lib

set(MATLAB_FOUND 0)
if(WIN32)
  if(${CMAKE_GENERATOR} MATCHES "Visual Studio 11")
    GET_FILENAME_COMPONENT(MATLAB_ROOT  "[HKEY_LOCAL_MACHINE\\SOFTWARE\\MathWorks\\MATLAB\\8.0;MATLABROOT]" ABSOLUTE CACHE)
    set(MATLAB_LIB_SEARCH "${MATLAB_ROOT}/extern/lib/win64/microsoft/")
    set(MATLAB_INCLUDE_SEARCH "${MATLAB_ROOT}/extern/include")
  else(${CMAKE_GENERATOR} MATCHES "Visual Studio 11")
    if(MATLAB_FIND_REQUIRED)
      message(FATAL_ERROR "Generator not compatible: ${CMAKE_GENERATOR}")
    endif(MATLAB_FIND_REQUIRED)
  endif(${CMAKE_GENERATOR} MATCHES "Visual Studio 11")
  find_library(MATLAB_MEX_LIBRARY
    libmex
    ${MATLAB_LIB_SEARCH}
    )
  find_library(MATLAB_MX_LIBRARY
    libmx
    ${MATLAB_LIB_SEARCH}
    )
  find_library(MATLAB_ENG_LIBRARY
    libeng
    ${MATLAB_LIB_SEARCH}
    )
  find_path(MATLAB_INCLUDE_DIRS
    "mex.h"
    ${MATLAB_INCLUDE_SEARCH}
    )
else(WIN32)
  if(CMAKE_SIZEOF_VOID_P EQUAL 4)
    # Regular x86
    set(MATLAB_ROOT /usr/local/MATLAB/R2012b/bin/glnxa86/)
  else(CMAKE_SIZEOF_VOID_P EQUAL 4)
    # AMD64:
    set(MATLAB_ROOT "/usr/local/MATLAB/R2012b/bin/glnxa64/"
                    "/usr/local/MATLAB/R2013a/bin/glnxa64/"
                    "/opt/MATLAB/R2012b/bin/glnxa64/"
                    "/opt/MATLAB/R2013a/bin/glnxa64/")
  endif(CMAKE_SIZEOF_VOID_P EQUAL 4)
  find_library(MATLAB_MEX_LIBRARY
    mex
    ${MATLAB_ROOT}
    )
  find_library(MATLAB_MX_LIBRARY
    mx
    ${MATLAB_ROOT}
    )
  find_library(MATLAB_ENG_LIBRARY
    eng
    ${MATLAB_ROOT}
    )
  find_path(MATLAB_INCLUDE_DIRS
    "mex.h"
    "/usr/local/MATLAB/R2012b/extern/include"
    "/opt/MATLAB/R2012b/extern/include"
    "/usr/local/MATLAB/R2013a/extern/include"
    "/opt/MATLAB/R2013a/extern/include"
    )
endif(WIN32)

# This is common to UNIX and Win32:
set(MATLAB_LIBRARIES
  ${MATLAB_MEX_LIBRARY}
  ${MATLAB_MX_LIBRARY}
  ${MATLAB_ENG_LIBRARY}
)

if(MATLAB_INCLUDE_DIRS AND MATLAB_LIBRARIES)
  set(MATLAB_FOUND 1)
  message(STATUS "Matlab found.")
else(MATLAB_INCLUDE_DIRS AND MATLAB_LIBRARIES)
  message(STATUS "Matlab not found.")
endif(MATLAB_INCLUDE_DIRS AND MATLAB_LIBRARIES)

mark_as_advanced(
  MATLAB_LIBRARIES
  MATLAB_MEX_LIBRARY
  MATLAB_MX_LIBRARY
  MATLAB_ENG_LIBRARY
  MATLAB_INCLUDE_DIRS
  MATLAB_FOUND
  MATLAB_ROOT
)

