# CMake file for generating Python modules.
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(ANTTWEAKBAR)

# Compiler flags
#if(CMAKE_COMPILER_IS_GNUCXX)
#    set(CMAKE_CXX_FLAGS "-O3 -fopenmp")        ## Optimize
#    set(CMAKE_CXX_FLAGS "-O3 -fPIC")        ## Optimize
#    set(CMAKE_EXE_LINKER_FLAGS "-s -fPIC")  ## Strip binary
#    set(CMAKE_EXE_SHARED_FLAGS "-s -fPIC")  ## Strip binary
#    set(CMAKE_EXE_MODULE_FLAGS "-s -fPIC")  ## Strip binary
#    set(CMAKE_CXX_FLAGS "-g")        ## Debug
#endif()

# Base research path
SET(RESEARCH_PATH "${CMAKE_SOURCE_DIR}/../../..")

# Common files
SET(COMMON_PATH "${RESEARCH_PATH}/Common")

# CMake finder files
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${COMMON_PATH}/cmake")

# swig interface files
INCLUDE_DIRECTORIES("${COMMON_PATH}/swig")

SET(CMAKE_SWIG_FLAGS "-builtin")

##########################
# Build AntTweakBar library and Python module.
# Note: Must use clang for Objective C++ support.
##########################

IF(APPLE)
  include_directories(/usr/X11R6/include/)
  include_directories(/usr/include/malloc)
  link_directories(/usr/X11R6/lib)
ENDIF (APPLE)

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

SET(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-fPIC")
SET(CMAKE_EXE_SHARED_FLAGS ${CMAKE_EXE_SHARED_FLAGS} "-fPIC")
# set path to include MacPorts rather thanl local python libraries. 
IF(APPLE)
    SET(CMAKE_LIBRARY_PATH /opt/local/lib ${CMAKE_LIBRARY_PATH})
    ADD_DEFINITIONS(
    -O3 
    -w -fPIC 
    -fno-strict-aliasing 
    -D_MACOSX 
    -ObjC++ 
    -D__PLACEMENT_NEW_INLINE 
    -fvisibility-inlines-hidden
    )
ELSE()
    ADD_DEFINITIONS(
    -O3 
    -w 
    -fPIC 
    -fno-strict-aliasing 
    -D_UNIX 
    -D__PLACEMENT_NEW_INLINE
    -fvisibility-inlines-hidden
    )
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

 
