#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.60])
AC_INIT([db_engine], [0.0.2], [asy5178@163.com])

# Checks for programs.
AC_PROG_INSTALL
AM_INIT_AUTOMAKE
AC_PROG_RANLIB

AC_PROG_CXX
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_MAKE_SET

# Checks for libraries.
# FIXME: Replace `main' with a function in `-lm':
AC_CHECK_LIB([m], [main])
# FIXME: Replace `main' with a function in `-lpthread':
AC_CHECK_LIB([pthread], [main])
# FIXME: Replace `main' with a function in `-lrt':
AC_CHECK_LIB([rt], [main])
# FIXME: Replace `main' with a function in `-lz':
AC_CHECK_LIB([z], [main])

# Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h fcntl.h netdb.h netinet/in.h stdint.h stdlib.h sys/socket.h unistd.h])
#AX_CXX_COMPILE_STDCXX_11([noext], [mandatory])

# Checks for typedefs, structures, and compiler characteristics.
# AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_INT32_T
AC_TYPE_SIZE_T
AC_TYPE_UINT32_T

# Checks for library functions.
# AC_FUNC_FORK
AC_FUNC_MALLOC
AC_CHECK_FUNCS([bzero dup2 gethostname memset socket])

CXXFLAGS=-std=c++11

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 src/client/Makefile
                 src/common/Makefile
                 src/engine_db/Makefile
                 src/proto/Makefile
                 src/rpc/Makefile
                 src/rpc/rpc_client/Makefile
                 src/rpc/rpc_server/Makefile
                 src/server/Makefile
                 src/test/Makefile])
AC_OUTPUT
