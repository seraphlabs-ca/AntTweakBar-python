# CMake file for generating Python modules.
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# build library

FIND_PACKAGE(GLUT REQUIRED)
FIND_PACKAGE(OpenGL REQUIRED)
INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})

FIND_PACKAGE(X11 REQUIRED)
INCLUDE_DIRECTORIES(${X11_INCLUDE_DIR})

FIND_PACKAGE(GLFW3 REQUIRED)
INCLUDE_DIRECTORIES(${GLFW_INCLUDE_DIRS})

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../../packages/AntTweakBar/src)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../../packages/AntTweakBar/include)

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
    SET(SRC_FILES ${SRC_FILES} "${CMAKE_CURRENT_SOURCE_DIR}/../../packages/AntTweakBar/src/${F}")
ENDFOREACH(F)


# AntTweakBar library

SET(ANTTWEAKBAR_LIBRARIES
    ${OPENGL_LIBRARIES}
    ${GLUT_LIBRARIES}
    ${X11_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
    ${GL_LIBRARIES})
BUILD_LIBRARY(AntTweakBar "${SRC_FILES}" "${ANTTWEAKBAR_LIBRARIES}")

# AntTweakBar python module

SET(SWIG_SRC_FILES AntTweakBarSWIG.cpp
                   AntTweakBarSWIG.h)

SET(ANTTWEAKBAR_SWIG_LIBRARIES
    AntTweakBar
    ${ANTTWEAKBAR_LIBRARIES}
    )

SWIG_BUILD_MODULE_PY(AntTweakBarSWIG AntTweakBarSWIG.i "${ANTTWEAKBAR_SWIG_LIBRARIES}" "${SWIG_SRC_FILES}")
