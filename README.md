GL Set Version
==============

A library to spoof GL version numbers.

WARNING: This library is not meant for use by end-users. It's meant for hacky workarounds and
         debugging purposes only.

If you happen to know for certain that your OpenGL implementation supports a specific version
but the GL library and the application are miscommunicating version support then this library
may be for you.

Specifically, the AMD proprietary OpenGL libraries recently changed the way they advertise
GL versions -- instead of reporting the highest version first it reports the lowest supported
version first. This version string format is highly impractical because it diverges so greatly
from the specification and standard practice. The result is applications parse only the initial
portion of the version string and believe that the OpenGL library does not support their needs.
This causes the applications to exit.

By launching the application with GL Set Version preloaded we can change the version string
so that applications can parse it favorably and everything else passes through to the original
GL library.

## Compilation

Use autotools and automake to configure and build:
~~~~
./autogen.sh
./configure CFLAGS='-g -O0' --prefix=/usr --sysconfdir=/etc --libdir=/usr/lib
make
make install
~~~~

## Usage

Create a script setting the environment variables that the glversion `LD_PRELOAD` library uses:
~~~~
#!/bin/bash

export GL_MAJOR_VERSION="4"
export GL_MINOR_VERSION="4"
export GL_VERSION="${GL_MAJOR_VERSION}.${GL_MINOR_VERSION}"
export LD_PRELOAD=/path/to/libglversion.so.1.0.2
~~~~

Then run your executable after sourcing the script. Alternately you could make your script run the GL program after setting the environment variables:
~~~~
#!/bin/bash

export GL_MAJOR_VERSION="4"
export GL_MINOR_VERSION="4"
export GL_VERSION="${GL_MAJOR_VERSION}.${GL_MINOR_VERSION}"
export LD_PRELOAD=/path/to/libglversion.so.1.0.2

exec "$@"
~~~~

## Testing

~~~~
make check
~~~~


## Other, More Featureful, Tracing and Debugging Tools

- apitrace
- vogl
