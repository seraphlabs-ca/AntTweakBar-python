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

%apply (int DIM1, double* INPLACE_ARRAY1)
        {(int i, double* M)}
%apply (int DIM1, unsigned char* INPLACE_ARRAY1)
        {(int i, unsigned char* M)}
%apply (int DIM1, double* IN_ARRAY1)
        {(int i, double *quat),
         (int i, double *axis),
         (int i, double *q1), 
         (int j, double *q2)}
%apply (int* DIM1, double** ARGOUTVIEWM_ARRAY1)
        {(int* j, double** quat),
        (int* k, double **qout)}
%apply (int* DIM1, int* DIM2, double** ARGOUTVIEWM_ARRAY2)
        {(int* j, int* k, double **mat)}

%include "std_string.i"
%include "typemaps.i"
%include "std_list.i"

%include "common.i"

// Ignore Windows-related symbols in AntTweakBar 1.16
%ignore TwEventWin;

%include "AntTweakBar.h"
%include "AntTweakBarSWIG.h"


