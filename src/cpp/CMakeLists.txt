CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(AntTweakBar)



# setup header
INCLUDE($ENV{CMAKE_COMMON_HEADER_FILE})

# include root path
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

#build files
ADD_SUBDIRECTORY(anttweakbar)

# setup footer
INCLUDE(FooterConfig)
