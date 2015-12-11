IF (DEFINED FIND_CXXTEST_CMAKE_INCLUDED)
    RETURN()
ENDIF (DEFINED FIND_CXXTEST_CMAKE_INCLUDED)
SET(FIND_CXXTEST_CMAKE_INCLUDED true)

FIND_PROGRAM(CXXTESTGEN
    NAMES cxxtestgen
    PATHS "${CXXTEST_PATH}/bin"
          "${PROJECT_SOURCE_DIR}/cxxtest/bin"
          "${PROJECT_SOURCE_DIR}/lib/cxxtest/bin"
          "${PROJECT_BINARY_DIR}/cxxtest/bin"
          "${PROJECT_BINARY_DIR}/lib/cxxtest/bin"
          /usr/bin
          /bin
          )

FIND_PATH(CXXTEST_INCLUDES
    NAMES "cxxtest/TestSuite.h"
    PATHS "${CXXTEST_PATH}"
          "${PROJECT_SOURCE_DIR}/cxxtest/"
          "${PROJECT_SOURCE_DIR}/lib/cxxtest/"
          )

IF(NOT CXXTESTGEN)
    MESSAGE(FATAL_ERROR "Unable to find 'cxxtestgen'")
    SET(CXXTEST_FOUND false)
ELSEIF(NOT CXXTEST_INCLUDES)
    SET(CXXTEST_FOUND false)
ELSE(NOT CXXTESTGEN)
    SET(CXXTEST_FOUND true)
    SET(CXXTEST_ROOT ${CXXTEST_INCLUDES})
ENDIF(NOT CXXTESTGEN)

SET(CXXTEST_CMAKE_MODULES_PATH ".")
INCLUDE("${CXXTEST_CMAKE_MODULES_PATH}/CxxTest.cmake")

