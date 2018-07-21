#ifndef GLD_GL_H
#define GLD_GL_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define GL_COLOR_BUFFER_BIT 2
#define GL_DEPTH_BUFFER_BIT 3

#define GL_ARRAY_BUFFER 56

#define GL_STATIC_DRAW 34

#define GL_FLOAT 4
#define GL_UNSIGNED_BYTE 5

#define GL_TRIANGLES 3

#define GL_VERTEX_ARRAY 7
#define GL_NORMAL_ARRAY 8
#define GL_TEXTURE_COORD_ARRAY 9

#define GL_MODELVIEW 5
#define GL_PROJECTION 7

#define GL_TEXTURE_2D 9
#define GL_DEPTH_TEST 10
#define GL_BLEND 11
#define GL_CULL_FACE 12

#define GL_SRC_ALPHA 4
#define GL_ONE 5
#define GL_ONE_MINUS_SRC_ALPHA 6

#define GL_TEXTURE_MIN_FILTER 2
#define GL_TEXTURE_MAG_FILTER 5

#define GL_LINEAR 2

#define GL_RGB 7
#define GL_RGBA 5

typedef float GLclampf;
typedef float GLfloat;
typedef int GLbitfield;
typedef int GLint;
typedef unsigned int GLuint;
typedef unsigned int GLsizei;
typedef unsigned int GLenum;
typedef size_t GLsizeiptr;
typedef void GLvoid;
typedef double GLdouble;

void glViewport(GLint x, GLint y, GLsizei width, GLsizei height);
void glClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
void glClear(GLbitfield mask);
void glGenBuffers(GLsizei n, GLuint *buffers);
void glDeleteBuffers(GLsizei n, const GLuint *buffers);

void glBindBuffer(GLenum target, GLuint buffer);
/*void glBufferData(GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage);*/
void glBufferData(GLenum target, GLsizeiptr size, const GLfloat *data, GLenum usage);
void glVertexPointer(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
void glDrawArrays(GLenum mode, GLint first, GLsizei count);
void glEnableClientState(GLenum cap);
void glDisableClientState(GLenum cap);
void glRotatef(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
void glPushMatrix();
void glPopMatrix();
void glMatrixMode(GLenum mode);
void glLoadMatrixf(const GLfloat *m);
void glLoadIdentity();
void glOrtho(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble nearVal, GLdouble farVal);
void glTranslatef(GLfloat x, GLfloat y, GLfloat z);
void glScalef(GLfloat x, GLfloat y, GLfloat z);
void glBlendFunc(GLenum sfactor, GLenum dfactor);

void glGenTextures(GLsizei n, GLuint *textures);
void glBindTexture(GLenum target, GLuint texture);
void glTexCoordPointer(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
/*void glTexParameteri(GLenum target, GLenum pname, GLint param);*/
void glGenerateMipmap(GLenum target);
void glTexImage2D(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height,
  GLint border, GLenum format, GLenum type, const GLvoid *data);
  /*GLint border, GLenum format, GLenum type, const GLfloat *data);*/

void glNormalPointer(GLenum type, GLsizei stride, const GLvoid *pointer);

void glEnable(GLenum cap);
void glDisable(GLenum cap);

int gldGetCurrentId();
void gldSetCurrentId(int id);

#ifdef __cplusplus
}
#endif

#endif
