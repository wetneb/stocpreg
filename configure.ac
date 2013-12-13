AC_INIT([stocpreg], [0.1], [antonin@delpeuch.eu], [stocpreg],
[http://github.com/wetneb/stocpreg])
AC_PREREQ([2.59])
AM_INIT_AUTOMAKE([1.10 no-define foreign subdir-objects])
AC_PROG_CXX
AC_CONFIG_FILES([Makefile])

# Get boost library and include locations
AC_ARG_WITH([boost-include-path],
              [AS_HELP_STRING([--with-boost-include-path],
                                  [location of the boost headers, defaults to /usr/include])],
                                    [BOOST_CFLAGS="-I$withval"],
                                      [BOOST_CFLAGS='-I/usr/include'])
AC_SUBST([BOOST_CFLAGS])

AC_ARG_WITH([boost-lib-path],
              [AS_HELP_STRING([--with-boost-lib-path], [location of the boost libraries])],
                [BOOST_LIBS="-L$withval -lboost_serialization"],
                  [BOOST_LIBS='-lboost_serialization'])
AC_SUBST([BOOST_LIBS])

AC_OUTPUT
