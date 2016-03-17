# CMake file for generating Python modules.
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(AntTweakBar)

# Base research path
SET(RESEARCH_PATH "${CMAKE_SOURCE_DIR}/../../..")

# setup header
INCLUDE(${RESEARCH_PATH}/Common/cmake/HeaderConfig.cmake)

# build library

FIND_PACKAGE(SWIG REQUIRED)
INCLUDE(${SWIG_USE_FILE})

FIND_PACKAGE(PythonLibs REQUIRED)
INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_PATH})

FIND_PACKAGE(Threads REQUIRED)
FIND_PACKAGE(GLUT REQUIRED)
FIND_PACKAGE(OpenGL REQUIRED)
INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})

FIND_PACKAGE(X11 REQUIRED)
INCLUDE_DIRECTORIES(${X11_INCLUDE_DIR})

FIND_PACKAGE(Numpy REQUIRED)
INCLUDE_DIRECTORIES(${NUMPY_INCLUDE_DIR})

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../packages/AntTweakBar/src)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../packages/AntTweakBar/include)

# set path to include MacPorts rather than local python libraries.
IF(APPLE)
    ADD_DEFINITIONS(
    -ObjC++
    -D__PLACEMENT_NEW_INLINE
    )
ELSE()
ENDIF (APPLE)

SET(CMAKE_C_FLAGS ${CMAKE_CXX_FLAGS})

# set all relevant source names
# AntTWeakBar1.14
#SET(SRC_FILES_NAME TwColors.cpp TwFonts.cpp TwOpenGL.cpp TwBar.cpp TwMgr.cpp
#    TwPrecomp.cpp LoadOGL.cpp TwEventGLFW.c TwEventGLUT.c TwEventSDL.c
#    TwEventSDL12.c TwEventSDL13.c TwEventSFML.cpp AntPerfTimer.h
#    LoadOGL.h MiniSDL12.h resource.h TwDirect3D10.h TwFonts.h TwOpenGLCore.h
#    d3d10vs2003.h MiniGLFW.h MiniSDL13.h TwBar.h TwDirect3D11.h TwGraph.h
#    TwOpenGL.h LoadOGLCore.h MiniGLUT.h MiniSFML16.h TwColors.h TwDirect3D9.h
#    TwMgr.h TwPrecomp.h ../include/AntTweakBar.h)

# AntTWeakBar1.16
SET(SRC_FILES_NAME TwColors.cpp TwFonts.cpp TwOpenGL.cpp TwOpenGLCore.cpp
    TwBar.cpp TwMgr.cpp LoadOGL.cpp LoadOGLCore.cpp TwEventGLFW.c TwEventGLUT.c
    TwEventSDL.c TwEventSDL12.c TwEventSDL13.c TwEventSFML.cpp)

FOREACH (F ${SRC_FILES_NAME})
    SET(SRC_FILES ${SRC_FILES} "${CMAKE_SOURCE_DIR}/../packages/AntTweakBar/src/${F}")
ENDFOREACH(F)


# AntTweakBar library
ADD_LIBRARY(AntTweakBar ${SRC_FILES})
TARGET_LINK_LIBRARIES(AntTweakBar
    ${OPENGL_LIBRARIES}
    ${GLUT_LIBRARIES}
    ${X11_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
    ${GL_LIBRARIES})

# AntTweakBar python module
SET(CMAKE_SWIG_FLAGS ${CMAKE_SWIG_FLAGS} "-builtin")

SET(SWIG_SRC_FILES AntTweakBarSWIG.cpp
                   AntTweakBarSWIG.h)

SET_SOURCE_FILES_PROPERTIES(AntTweakBar.i PROPERTIES CPLUSPLUS ON)
SWIG_ADD_MODULE(AntTweakBar python AntTweakBar.i ${SWIG_SRC_FILES})
SWIG_LINK_LIBRARIES(AntTweakBar AntTweakBar
    ${PYTHON_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${GLUT_LIBRARIES}
    ${X11_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
    ${GL_LIBRARIES})

# install files
# install files
INSTALL(TARGETS AntTweakBar
        DESTINATION ${PROJECT_LIBRARY_INSTALL_PATH})
INSTALL(FILES "${CMAKE_CURRENT_SOURCE_DIR}/AntTweakBarSWIG.h"
        DESTINATION ${PROJECT_INCLUDE_INSTALL_PATH})
INSTALL(FILES "${CMAKE_CURRENT_SOURCE_DIR}/../packages/AntTweakBar/include/AntTweakBar.h"
        DESTINATION ${PROJECT_INCLUDE_INSTALL_PATH})
INSTALL(FILES "${CMAKE_CURRENT_BINARY_DIR}/_AntTweakBar.so"
        DESTINATION ${PROJECT_PYTHON_INSTALL_PATH})
INSTALL(FILES "${CMAKE_CURRENT_BINARY_DIR}/AntTweakBar.py"
        DESTINATION ${PROJECT_PYTHON_INSTALL_PATH})

# install configuration
# INCLUDE(${RESEARCH_PATH}/Common/cmake/InstallConfig.cmake)

 # setup footer
INCLUDE(${RESEARCH_PATH}/Common/cmake/FooterConfig.cmake)

# generate documentations
INCLUDE(${RESEARCH_PATH}/Common/cmake/DocConfig.cmake)

