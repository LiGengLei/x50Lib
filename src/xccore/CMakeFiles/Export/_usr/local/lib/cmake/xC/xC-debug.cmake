#----------------------------------------------------------------
# Generated CMake target import file for configuration "DEBUG".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "xC-core" for configuration "DEBUG"
set_property(TARGET xC-core APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(xC-core PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "/usr/local/lib/libxC-core.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS xC-core )
list(APPEND _IMPORT_CHECK_FILES_FOR_xC-core "/usr/local/lib/libxC-core.a" )

# Import target "xC-math" for configuration "DEBUG"
set_property(TARGET xC-math APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(xC-math PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "/usr/local/lib/libxC-math.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS xC-math )
list(APPEND _IMPORT_CHECK_FILES_FOR_xC-math "/usr/local/lib/libxC-math.a" )

# Import target "xC-test" for configuration "DEBUG"
set_property(TARGET xC-test APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(xC-test PROPERTIES
  IMPORTED_LOCATION_DEBUG "/usr/local/bin/xC-test"
  )

list(APPEND _IMPORT_CHECK_TARGETS xC-test )
list(APPEND _IMPORT_CHECK_FILES_FOR_xC-test "/usr/local/bin/xC-test" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
