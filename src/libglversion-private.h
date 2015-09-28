/*
  libglversion - Set GL Version

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

#ifndef _LIBGLVERSION_PRIVATE_H_
#define _LIBGLVERSION_PRIVATE_H_

#include <stdlib.h>
#include <stdbool.h>

#ifndef HAVE_SECURE_GETENV
#  ifdef HAVE___SECURE_GETENV
#    define secure_getenv __secure_getenv
#  else
#    error neither secure_getenv nor __secure_getenv is available
#  endif
#endif

#define GLVERSION_EXPORT __attribute__ ((visibility("default")))
#endif
