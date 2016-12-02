set(MODULE_NAME "${PROJECT_NAME}-${SubProject}")

find_package(Boost REQUIRED COMPONENTS regex)

include_directories(${Boost_INCLUDE_DIRS})

add_library(${MODULE_NAME}
  definition.h
  engine.h
  engine.cpp
)

add_executable(xclng_test
   xclng_test.cpp
)

target_link_libraries(xclng_test
  ${MODULE_NAME}
  ${Boost_LIBRARIES}
)

# Output
set(LIBRARY_${SubProject}
  ${MODULE_NAME}
  ${CMAKE_THREAD_LIBS_INIT}
  ${Boost_LIBRARIES}
  PARENT_SCOPE)

# Install
set_target_properties(${MODULE_NAME} PROPERTIES PUBLIC_HEADER "definition.h")
set_target_properties(${MODULE_NAME} PROPERTIES PUBLIC_HEADER "engine.h")

install(TARGETS ${MODULE_NAME}
  EXPORT ${PROJECT_NAME}
  RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin
  LIBRARY DESTINATION "${INSTALL_LIB_DIR}" COMPONENT shlib
  ARCHIVE DESTINATION "${INSTALL_LIB_DIR}" COMPONENT lib
  PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}/${PROJECT_NAME}/${MODULE_NAME}"
  COMPONENT dev
)
