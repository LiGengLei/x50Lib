set(MODULE_NAME "${PROJECT_NAME}-${SubProject}")

find_package(xC REQUIRED)
find_package(Boost REQUIRED COMPONENTS system thread)
find_package(Threads)

include_directories(
  ${Boost_INCLUDE_DIRS}
  ${XC_INCLUDE_DIRS}
)

# library
add_library(${MODULE_NAME}
  protocol.cpp
)

target_link_libraries( ${MODULE_NAME}
  ${CMAKE_THREAD_LIBS_INIT}
  ${Boost_LIBRARIES}
)

set(LIBRARY_${SubProject}
  ${MODULE_NAME}
  ${CMAKE_THREAD_LIBS_INIT}
  ${Boost_LIBRARIES}
  PARENT_SCOPE)

set_target_properties(${MODULE_NAME} PROPERTIES PUBLIC_HEADER "protocol.h")

install(TARGETS ${MODULE_NAME}
  EXPORT ${PROJECT_NAME}
  RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin
  LIBRARY DESTINATION "${INSTALL_LIB_DIR}" COMPONENT shlib
  ARCHIVE DESTINATION "${INSTALL_LIB_DIR}" COMPONENT lib
  PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}/${PROJECT_NAME}/${MODULE_NAME}"
  COMPONENT dev
)

# test
add_library(${MODULE_NAME}_teriminal
  teriminal.cpp
)

target_link_libraries( ${MODULE_NAME}_teriminal
  ${MODULE_NAME}
)

set(LIBRARY_${SubProject}
  ${MODULE_NAME}
  ${CMAKE_THREAD_LIBS_INIT}
  ${Boost_LIBRARIES}
  PARENT_SCOPE)
