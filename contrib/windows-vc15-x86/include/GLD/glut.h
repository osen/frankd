#ifndef GLUT_H
#define GLUT_H

#include "gl.h"

#ifdef __cplusplus
extern "C" {
#endif

#define GLUT_DOUBLE 2
#define GLUT_RGBA 4
#define GLUT_DEPTH 6

#define GLUT_ELAPSED_TIME 3
#define GLUT_WINDOW_WIDTH 4
#define GLUT_WINDOW_HEIGHT 5

void glutInit(int *argcp, char **argv);
void glutInitDisplayMode(unsigned int mode);
void glutInitWindowSize(int width, int height);
int glutCreateWindow(const char *name);
void glutDisplayFunc(void (*func)());
void glutIdleFunc(void (*func)());
void glutMainLoop(void);
void glutSwapBuffers(void);
void glutPostRedisplay();
void glutKeyboardFunc(void (*func)(unsigned char key, int x, int y));
void glutKeyboardUpFunc(void (*func)(unsigned char key, int x, int y));
void glutMotionFunc(void (*func)(int x, int y));
void glutMouseFunc(void (*func)(int button, int state, int x, int y));
int glutGet(GLenum state);
void glutLeaveMainLoop();
void glutMainLoopEvent();

/* Extensions */
void glutdCleanup();

#ifdef __cplusplus
}
#endif

#endif
