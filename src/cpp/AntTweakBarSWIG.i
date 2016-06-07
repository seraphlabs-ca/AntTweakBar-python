%module AntTweakBar
#ifndef PySwigIterator
#define PySwigIterator AntTweakBar_PySwigIterator
#endif
%{
#define SWIG_FILE_WITH_INIT
#include "AntTweakBar.h"
#include "AntTweakBarSWIG.h"
%}

%include "numpy.i"

%init %{
    import_array();
%}

%include "AntTweakBar.i"
