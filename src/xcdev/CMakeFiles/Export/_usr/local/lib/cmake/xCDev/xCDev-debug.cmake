#----------------------------------------------------------------
# Generated CMake target import file for configuration "DEBUG".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "xCDev-core" for configuration "DEBUG"
set_property(TARGET xCDev-core APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(xCDev-core PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "-lpthread;/usr/lib/x86_64-linux-gnu/libboost_system.so;/usr/lib/x86_64-linux-gnu/libboost_thread.so"
  IMPORTED_LOCATION_DEBUG "/usr/local/lib/libxCDev-core.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS xCDev-core )
list(APPEND _IMPORT_CHECK_FILES_FOR_xCDev-core "/usr/local/lib/libxCDev-core.a" )

# Import target "xCDev-PMAC" for configuration "DEBUG"
set_property(TARGET xCDev-PMAC APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(xCDev-PMAC PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "-lpthread;/usr/lib/x86_64-linux-gnu/libboost_system.so;/usr/lib/x86_64-linux-gnu/libboost_thread.so"
  IMPORTED_LOCATION_DEBUG "/usr/local/lib/libxCDev-PMAC.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS xCDev-PMAC )
list(APPEND _IMPORT_CHECK_FILES_FOR_xCDev-PMAC "/usr/local/lib/libxCDev-PMAC.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
