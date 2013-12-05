/*
 * This file adds wrapper functions to support easier Python access.
 */

#include "AntTweakBarSWIG.h"
#include <GL/glut.h>

#include <math.h>

// FIXME: use TwCopyStdStringToClientFunc to make RW. Currently only RO.
// Adding Python interface
int TwAddVarStringRW(TwBar *bar, const char *name, std::string var, const char *def) {
	return TwAddVarRW(bar, name, TW_TYPE_STDSTRING, (void*)&var, def);
}

int TwAddVarArrayRW(TwBar *bar, const char *name, TwType type, int i, double *M, const char *def) {
	return TwAddVarRW(bar, name, type, (void*)M, def);
}

int TwAddVarArrayBoolRW(TwBar *bar, const char *name, int i, unsigned char *M, const char *def) {
	return TwAddVarRW(bar, name, TW_TYPE_BOOL8, (void*)M, def);
}

int TwAddVarStringRO(TwBar *bar, const char *name, std::string var, const char *def) {
	return TwAddVarRO(bar, name, TW_TYPE_STDSTRING, (void*)&var, def);
}

int TwAddVarArrayRO(TwBar *bar, const char *name, TwType type, int i, double *M, const char *def) {
	return TwAddVarRO(bar, name, type, (void*)M, def);
}

// Supply Quaternions functionality

// Routine to set a quaternion from a rotation axis and angle
// ( input axis = double[3] angle = double  output: quat = double[4] )
void SetQuaternionFromAxisAngle(int i, double *axis, double angle, int* j, double **quat)
{
    double sina2, norm;
    sina2 = (double)sin(0.5f * angle);
    norm = (double)sqrt(axis[0]*axis[0] + axis[1]*axis[1] + axis[2]*axis[2]);

    (*quat) = new double[4];
    (*quat)[0] = sina2 * axis[0] / norm;
    (*quat)[1] = sina2 * axis[1] / norm;
    (*quat)[2] = sina2 * axis[2] / norm;
    (*quat)[3] = (double)cos(0.5f * angle);
    (*j) = 4;
}


// Routine to convert a quaternion to a 4x4 matrix
// ( input: quat = double[4]  output: mat = double[4*4] )
void ConvertQuaternionToMatrix(int i, double *quat, int* j, int* k, double **mat)
{
    double yy2 = 2.0f * quat[1] * quat[1];
    double xy2 = 2.0f * quat[0] * quat[1];
    double xz2 = 2.0f * quat[0] * quat[2];
    double yz2 = 2.0f * quat[1] * quat[2];
    double zz2 = 2.0f * quat[2] * quat[2];
    double wz2 = 2.0f * quat[3] * quat[2];
    double wy2 = 2.0f * quat[3] * quat[1];
    double wx2 = 2.0f * quat[3] * quat[0];
    double xx2 = 2.0f * quat[0] * quat[0];

    (*mat) = new double[16];
    (*mat)[0*4+0] = - yy2 - zz2 + 1.0f;
    (*mat)[0*4+1] = xy2 + wz2;
    (*mat)[0*4+2] = xz2 - wy2;
    (*mat)[0*4+3] = 0;
    (*mat)[1*4+0] = xy2 - wz2;
    (*mat)[1*4+1] = - xx2 - zz2 + 1.0f;
    (*mat)[1*4+2] = yz2 + wx2;
    (*mat)[1*4+3] = 0;
    (*mat)[2*4+0] = xz2 + wy2;
    (*mat)[2*4+1] = yz2 - wx2;
    (*mat)[2*4+2] = - xx2 - yy2 + 1.0f;
    (*mat)[2*4+3] = 0;
    (*mat)[3*4+0] = (*mat)[3*4+1] = (*mat)[3*4+2] = 0;
    (*mat)[3*4+3] = 1;

    (*j) = (*k) = 4;
}


// Routine to multiply 2 quaternions (ie, compose rotations)
// ( input q1 = double[4] q2 = double[4]  output: qout = double[4] )
void MultiplyQuaternions(int i, double *q1, int j, double *q2, int* k, double **qout)
{
	(*qout) = new double[4];
	(*qout)[0] = q1[3]*q2[0] + q1[0]*q2[3] + q1[1]*q2[2] - q1[2]*q2[1];
	(*qout)[1] = q1[3]*q2[1] + q1[1]*q2[3] + q1[2]*q2[0] - q1[0]*q2[2];
	(*qout)[2] = q1[3]*q2[2] + q1[2]*q2[3] + q1[0]*q2[1] - q1[1]*q2[0];
	(*qout)[3]  = q1[3]*q2[3] - (q1[0]*q2[0] + q1[1]*q2[1] + q1[2]*q2[2]);

	(*k) = 4;
}

void TwUpdateGLUTModifiersFunc() {
	TwGLUTModifiersFunc(glutGetModifiers);
}
