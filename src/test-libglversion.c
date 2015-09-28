/*
    test-libglversion.c - Test libglversion

    Copyright (C) 2016 Matt Helsley <matt.helsley@gmail.com>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
*/

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h>
#include <errno.h>
#include <unistd.h>

#include <GL/gl.h>

int main(int argc, char *argv[])
{
	GLint maj = 0, min = 0;
	GLubyte *s;

	printf("version %s\n", VERSION);
	glGetIntegerv(GL_MAJOR_VERSION, &maj);
	glGetIntegerv(GL_MAJOR_VERSION, &min);
	s = glGetString(GL_VERSION);
	printf("GL_MAJOR_VERSION: %d\nGL_MINOR_VERSION: %d\nGL_VERSION: %s\n",
	       maj, min, s);
        return EXIT_SUCCESS;
}
