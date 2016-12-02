FILE(GLOB Eigen_MonotoneCubicInterpolation_SRCS "*.h")

INSTALL(FILES
  ${Eigen_MonotoneCubicInterpolation_SRCS}
  DESTINATION ${INCLUDE_INSTALL_DIR}/unsupported/Eigen/src/MonotoneCubicInterpolation COMPONENT Devel
  )
