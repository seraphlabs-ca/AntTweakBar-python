/*
 * This file adds wrapper functions to support easier Python access.
 */

#ifndef _ANTTWEAKBARSWIG_H_
#define _ANTTWEAKBARSWIG_H_

#include "AntTweakBar.h"
#include <string>

int TwAddVarStringRW(TwBar *bar, const char *name, std::string var, const char *def);
int TwAddVarArrayRW(TwBar *bar, const char *name, TwType type, int i, double *M, const char *def);
int TwAddVarArrayBoolRW(TwBar *bar, const char *name, int i, unsigned char *M, const char *def);

int TwAddVarStringRO(TwBar *bar, const char *name, std::string var, const char *def);
int TwAddVarArrayRO(TwBar *bar, const char *name, TwType type, int i, double *M, const char *def);

void SetQuaternionFromAxisAngle(int i, double *axis, double angle, int* j, double **quat);
void ConvertQuaternionToMatrix(int i, double *quat, int* j, int* k, double **mat);
void MultiplyQuaternions(int i, double *q1, int j, double *q2, int* k, double **qout);

// Updates TwGLUTModifiersFunc(glutGetModifiers). Assumes that glutInit was called.
void TwUpdateGLUTModifiersFunc();

#endif // _ANTTWEAKBARSWIG_H_
