/*
  libglversion - Set the GL Version

  Copyright (C) 2016 Matt Helsley <matt.helsley@gmail.com>

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdarg.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>

#include <GL/gl.h>
#include <dlfcn.h>

#include "libglversion-private.h"


/**
 * SECTION:libglversion
 */

#define xstringify(x) stringify(x)
#define stringify(x) #x

static inline int *__int_from_secure_envvar(const char *var, int *parsed)
{
	char *value = secure_getenv(var);
	if (value) {
		if (sscanf(value, "%d", parsed) != 1) {
			return NULL;
		}
		return parsed;
	}
	return NULL;
}

/**
 * Wrap glGet* and search for version-identifying pname parameters.
 *
 * Retrieve stored data pointer from library context. This might be useful
 * to access from callbacks like a custom logging function.
 *
 * Returns: stored userdata
 **/
GLVERSION_EXPORT const GLubyte *glGetString(GLenum pname)
{
	static GLubyte *(*orig_fn)(GLenum) = NULL;

	if (orig_fn == NULL) {
		typeof(orig_fn) fn = dlsym(RTLD_NEXT, "glGetString");
		orig_fn = fn;
	}
	if (!orig_fn) {
		abort();
	}
	if (pname == GL_VERSION) {
		return (const GLubyte *)secure_getenv("GL_VERSION");
	}
	return orig_fn(pname);
}

#define WRAP_GL_GET_INTEGER(typename, type) \
GLVERSION_EXPORT void glGet##typename (GLenum pname, type *ptr) \
{ \
	static void (*orig_fn)(GLenum, type *) = NULL; \
	int result; \
	\
	if (orig_fn == NULL) { \
		typeof(orig_fn) fn = dlsym(RTLD_NEXT, xstringify(glGet##typename)); \
		orig_fn = fn; \
	} \
	if (pname == GL_MAJOR_VERSION) { \
		if (__int_from_secure_envvar("GL_MAJOR_VERSION", &result) == &result) { \
			*ptr = result; \
			 return; \
		} \
	} else if (pname == GL_MINOR_VERSION) { \
		if (__int_from_secure_envvar("GL_MINOR_VERSION", &result) == &result) { \
			*ptr = result; \
			 return; \
		} \
	} \
	orig_fn(pname, ptr); \
}

WRAP_GL_GET_INTEGER(Integerv, GLint)
//WRAP_GL_GET_INTEGER(Integer64v, GLint64)

#define WRAP_GL_GET_INTEGER_INDEXED(typename, type) \
GLVERSION_EXPORT void glGet##typename (GLchar pname, GLuint index, type *ptr) \
{ \
	static void (*orig_fn)(GLenum, GLuint, type *) NULL; \
	int result; \
	\
	if (orig_fn == NULL) { \
		typeof(orig_fn) fn = dlsym(RTLD_NEXT, xstringify(glGet##typename)); \
		orig_fn = fn; \
	} \
	if (pname == GL_MAJOR_VERSION) { \
		if (__int_from_secure_envvar("GL_MAJOR_VERSION", &result) == &result) { \
			*ptr = result; \
			 return; \
		} \
	} else if (pname == GL_MINOR_VERSION) { \
		if (__int_from_secure_envvar("GL_MINOR_VERSION", &result) == &result) { \
			*ptr = result; \
			 return; \
		} \
	} \
	orig_fn(pname, index, ptr); \
}
//WRAP_GL_GET_INTEGER_INDEXED(Integeri_v, GLint)
//WRAP_GL_GET_INTEGER_INDEXED(Integer64i_v, GLint64)
