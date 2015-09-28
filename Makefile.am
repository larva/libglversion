EXTRA_DIST =
CLEANFILES =
ACLOCAL_AMFLAGS = -I m4 ${ACLOCAL_FLAGS}
AM_MAKEFLAGS = --no-print-directory

AM_CPPFLAGS = \
	-include $(top_builddir)/config.h \
	-DSYSCONFDIR=\""$(sysconfdir)"\" \
	-I${top_srcdir}/src

AM_CFLAGS = ${my_CFLAGS} \
	-fvisibility=hidden \
	-ffunction-sections \
	-fdata-sections

AM_LDFLAGS = \
	-Wl,--gc-sections \
	-Wl,--as-needed

SED_PROCESS = \
	$(AM_V_GEN)$(MKDIR_P) $(dir $@) && $(SED) \
	-e 's,@VERSION\@,$(VERSION),g' \
	-e 's,@prefix\@,$(prefix),g' \
	-e 's,@exec_prefix\@,$(exec_prefix),g' \
	-e 's,@libdir\@,$(libdir),g' \
	-e 's,@includedir\@,$(includedir),g' \
	< $< > $@ || rm $@

%.pc: %.pc.in Makefile
	$(SED_PROCESS)

LIBGL_CURRENT=1
LIBGL_REVISION=2
LIBGL_AGE=0

lib_LTLIBRARIES = src/libglversion.la

src_libglversion_la_SOURCES =\
	src/libglversion-private.h \
	src/libglversion.c

EXTRA_DIST += src/libglversion.sym

src_libglversion_la_LDFLAGS = $(AM_LDFLAGS) \
	-version-info $(LIBGL_CURRENT):$(LIBGL_REVISION):$(LIBGL_AGE) \
	-Wl,--version-script=$(top_srcdir)/src/libglversion.sym \
	-ldl
src_libglversion_la_DEPENDENCIES = ${top_srcdir}/src/libglversion.sym

# Build a 32-bit version as well
lib_LTLIBRARIES += src/libglversion32.la
src_libglversion32_la_SOURCES = $(src_libglversion_la_SOURCES)
src_libglversion32_la_CFLAGS = $(src_libglversion_la_CFLAGS) -m32
src_libglversion32_la_LDFLAGS = $(src_libglversion_la_LDFLAGS) -m32
src_libglversion32_la_DEPENDENCIES = ${top_srcdir}/src/libglversion.sym

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = src/libglversion.pc
EXTRA_DIST += src/libglversion.pc.in
CLEANFILES += src/libglversion.pc

TESTS = src/test-libglversion

check_PROGRAMS = src/test-libglversion
src_test_libglversion_SOURCES = src/test-libglversion.c
src_test_libglversion_LDFLAGS = $(AM_LDFLAGS) -lGL
#src_test_libglversion_LDADD = -lGL
