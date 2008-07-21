# - Check if the STDCALL function exists.
#   This works for non-cdecl functions (kernel32 functions, for example)
# CHECK_STDCALL_FUNCTION_EXISTS(FUNCTION FUNCTION_DUMMY_ARGS VARIABLE)
# - macro which checks if the stdcall function exists
#  FUNCTION_DECLARATION - the definition of the function ( e.g.: Sleep(500) )
#  VARIABLE - variable to store the result
#
# The following variables may be set before calling this macro to
# modify the way the check is run:
#
#  CMAKE_REQUIRED_FLAGS = string of compile command line flags
#  CMAKE_REQUIRED_DEFINITIONS = list of macros to define (-DFOO=bar)
#  CMAKE_REQUIRED_INCLUDES = list of include directories
#  CMAKE_REQUIRED_LIBRARIES = list of libraries to link
#  CMAKE_EXTRA_INCLUDE_FILES = list of extra includes to check in

MACRO(CHECK_STDCALL_FUNCTION_EXISTS FUNCTION_DECLARATION VARIABLE)
  IF("${VARIABLE}" MATCHES "^${VARIABLE}$")
    #get includes  
    SET(CHECK_STDCALL_FUNCTION_PREMAIN)
    FOREACH(def ${CMAKE_EXTRA_INCLUDE_FILES})
      SET(CHECK_STDCALL_FUNCTION_PREMAIN "${CHECK_STDCALL_FUNCTION_PREMAIN}#include \"${def}\"\n")
    ENDFOREACH(def)
    
    #add some default includes
    IF ( HAVE_WINDOWS_H )
        SET(CHECK_STDCALL_FUNCTION_PREMAIN "${CHECK_STDCALL_FUNCTION_PREMAIN}#include \"windows.h\"\n")
    ENDIF ( HAVE_WINDOWS_H )
    
    STRING(REGEX MATCH "([_a-zA-Z0-9]*)(.*)" CHECK_STDCALL_FUNCTION_EXISTS_FUNCTION ${FUNCTION_DECLARATION} )
    SET ( CHECK_STDCALL_FUNCTION_EXISTS_FUNCTION ${CMAKE_MATCH_1} )
    
    SET(MACRO_CHECK_STDCALL_FUNCTION_DEFINITIONS "${CMAKE_REQUIRED_FLAGS}")
    MESSAGE(STATUS "Looking for ${CHECK_STDCALL_FUNCTION_EXISTS_FUNCTION}")
    
    IF(CMAKE_REQUIRED_LIBRARIES)
      SET(CHECK_STDCALL_FUNCTION_EXISTS_ADD_LIBRARIES
        "-DLINK_LIBRARIES:STRING=${CMAKE_REQUIRED_LIBRARIES}")
    ELSE(CMAKE_REQUIRED_LIBRARIES)
      SET(CHECK_STDCALL_FUNCTION_EXISTS_ADD_LIBRARIES)
    ENDIF(CMAKE_REQUIRED_LIBRARIES)
    
    IF(CMAKE_REQUIRED_INCLUDES)
      SET(CHECK_STDCALL_FUNCTION_EXISTS_ADD_INCLUDES
        "-DINCLUDE_DIRECTORIES:STRING=${CMAKE_REQUIRED_INCLUDES}")
    ELSE(CMAKE_REQUIRED_INCLUDES)
      SET(CHECK_STDCALL_FUNCTION_EXISTS_ADD_INCLUDES)
    ENDIF(CMAKE_REQUIRED_INCLUDES)
    
    SET(CHECK_STDCALL_FUNCTION_DECLARATION ${FUNCTION_DECLARATION})
    CONFIGURE_FILE("${clucene-shared_SOURCE_DIR}/cmake/CheckStdCallFunctionExists.c.in"
      "${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeTmp/CheckStdCallFunctionExists.c" IMMEDIATE @ONLY)
    FILE(READ "${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeTmp/CheckStdCallFunctionExists.c"
      CHECK_STDCALL_FUNCTION_CONTENT)

    TRY_COMPILE(${VARIABLE}
      ${CMAKE_BINARY_DIR}
      "${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeTmp/CheckStdCallFunctionExists.c"
      COMPILE_DEFINITIONS ${CMAKE_REQUIRED_DEFINITIONS}
      CMAKE_FLAGS -DCOMPILE_DEFINITIONS:STRING=${MACRO_CHECK_STDCALL_FUNCTION_DEFINITIONS}
      "${CHECK_STDCALL_FUNCTION_EXISTS_ADD_LIBRARIES}"
      "${CHECK_STDCALL_FUNCTION_EXISTS_ADD_INCLUDES}"
      OUTPUT_VARIABLE OUTPUT)
    IF(${VARIABLE})
      SET(${VARIABLE} 1 CACHE INTERNAL "Have function ${FUNCTION_DECLARATION}")
      MESSAGE(STATUS "Looking for ${FUNCTION_DECLARATION} - found")
      FILE(APPEND ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeOutput.log 
        "Determining if the stdcall function ${FUNCTION_DECLARATION} exists passed with the following output:\n"
        "${OUTPUT}\nCheckStdCallFunctionExists.c:\n${CHECK_STDCALL_FUNCTION_CONTENT}\n\n")
    ELSE(${VARIABLE})
      MESSAGE(STATUS "Looking for ${FUNCTION_DECLARATION} - not found")
      SET(${VARIABLE} "" CACHE INTERNAL "Have function ${FUNCTION_DECLARATION}")
      FILE(APPEND ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeError.log 
        "Determining if the stdcall function ${FUNCTION_DECLARATION} exists failed with the following output:\n"
        "${OUTPUT}\nCheckStdCallFunctionExists.c:\n${CHECK_STDCALL_FUNCTION_CONTENT}\n\n")
    ENDIF(${VARIABLE})
  ENDIF("${VARIABLE}" MATCHES "^${VARIABLE}$")
ENDMACRO(CHECK_STDCALL_FUNCTION_EXISTS)