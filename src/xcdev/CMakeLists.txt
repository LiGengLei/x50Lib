cmake_minimum_required (VERSION 2.8)
###############################################################################
# Project
project(xCDev)
string(TOUPPER "${PROJECT_NAME}" UPPER_PROJECT_NAME)
string(TOLOWER "${PROJECT_NAME}" LOWER_PROJECT_NAME)

###############################################################################
# Project version code
set(PROJECT_MAJOR_VERSION 0)
set(PROJECT_MINOR_VERSION 0)
set(PROJECT_PATCH_VERSION 1)
set(PROJECT_VERSION ${PROJECT_MAJOR_VERSION}.${PROJECT_MINOR_VERSION}.${PROJECT_PATCH_VERSION})

###############################################################################
# Project build code
set(CMAKE_BUILD_TYPE DEBUG)

###############################################################################
# Offer the user the choice of overriding the installation directories
set(INSTALL_LIB_DIR lib CACHE PATH "Installation directory for libraries")
set(INSTALL_BIN_DIR bin CACHE PATH "Installation directory for executables")
set(INSTALL_INCLUDE_DIR include CACHE PATH "Installation directory for header files")

# Set install cmake directory
if(WIN32 AND NOT CYGWIN)
  set(DEF_INSTALL_CMAKE_DIR CMake)
else()
  set(DEF_INSTALL_CMAKE_DIR lib/cmake/${PROJECT_NAME})
endif()
set(INSTALL_CMAKE_DIR ${DEF_INSTALL_CMAKE_DIR}
    CACHE PATH "Installation directory for CMake files")

# Make relative paths absolute (needed later on)
foreach(p LIB BIN INCLUDE CMAKE)
  set(var INSTALL_${p}_DIR)
  if(NOT IS_ABSOLUTE "${${var}}")
    set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
  endif()
endforeach()

###############################################################################
# Set output directories
set(OUTPUT_LIB_DIR ${PROJECT_BINARY_DIR}/lib
    CACHE PATH "Output directory for libraries")
set(OUTPUT_BIN_DIR ${PROJECT_BINARY_DIR}/bin
    CACHE PATH "Output directory for executables")
file(MAKE_DIRECTORY ${OUTPUT_LIB_DIR})
file(MAKE_DIRECTORY ${OUTPUT_BIN_DIR})
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/${PROJECT_NAME})
set(LIBRARY_OUTPUT_PATH     ${OUTPUT_LIB_DIR})
set(EXECUTABLE_OUTPUT_PATH  ${OUTPUT_BIN_DIR})

###############################################################################
# configure script files
file(GLOB SCRIPTS_FILES
     RELATIVE "${PROJECT_SOURCE_DIR}/scripts"
     "${PROJECT_SOURCE_DIR}/scripts/*.sh")
foreach(SCRIPTS_FILE ${SCRIPTS_FILES})
        configure_file("${PROJECT_SOURCE_DIR}/scripts/${SCRIPTS_FILE}"
        "${OUTPUT_BIN_DIR}/${SCRIPTS_FILE}" @ONLY)
endforeach()

###############################################################################
# Set up include-directories
include_directories(${PROJECT_SOURCE_DIR} ${PROJECT_BINARY_DIR})

# Set CMake module path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmakes)

# Set sub-projects
set(SubProjects core PMAC)

set(OUTPUT_LIBRARIES "")
# Add sub-directories
foreach(SubProject ${SubProjects})
  set("LIBRARY_${SubProject}"  "")
  add_subdirectory(${LOWER_PROJECT_NAME}/${SubProject})
  set(OUTPUT_LINKS    ${OUTPUT_LINKS} ${LIBRARY_${SubProject}})
  set(OUTPUT_INCLUDES ${OUTPUT_INCLUDES} ${INCLUDE_${SubProject}})
endforeach(SubProject ${SubProjects})

###############################################################################
# Add all targets to the build-tree export set
foreach(SubProject ${SubProjects})
  export(TARGETS "${PROJECT_NAME}-${SubProject}" FILE "${PROJECT_BINARY_DIR}/${PROJECT_NAME}.cmake")
endforeach(SubProject ${SubProjects})

# Export the package for use from the build-tree
# (this registers the build-tree with a global CMake-registry)
export(PACKAGE ${PROJECT_NAME})

# Create a BuildTreeSettings.cmake file for the use from the build tree
configure_file(template/BuildTreeSettings.cmake.in
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}BuildTreeSettings.cmake" @ONLY)

# Create the Config.cmake and ConfigVersion files
file(RELATIVE_PATH CONF_REL_INCLUDE_DIR "${INSTALL_CMAKE_DIR}"
   "${INSTALL_INCLUDE_DIR}")
configure_file(template/Config.cmake.in
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake" @ONLY)
configure_file(template/ConfigVersion.cmake.in
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake" @ONLY)

# Install the Config.cmake and ConfigVersion.cmake
install(FILES
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
  DESTINATION "${INSTALL_CMAKE_DIR}" COMPONENT dev)

# Install the export set for use with the install-tree
install(EXPORT ${PROJECT_NAME} DESTINATION "${INSTALL_CMAKE_DIR}" COMPONENT dev)
