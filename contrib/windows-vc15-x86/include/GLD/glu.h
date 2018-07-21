#ifndef GLU_H
#define GLU_H

#include "gl.h"

#ifdef __cplusplus
extern "C" {
#endif

void gluPerspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar);

#ifdef __cplusplus
}
#endif

#endif
