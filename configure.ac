dnl Process this file with autoconf to produce a configure script.
dnl
AC_INIT([linux nfs-utils],[1.0.11],[nfs@lists.sf.net],[nfs-utils])
AC_CANONICAL_BUILD([])
AC_CANONICAL_HOST([])
AC_CONFIG_MACRO_DIR(aclocal)
AM_INIT_AUTOMAKE
AC_PREREQ(2.59)
AC_PREFIX_DEFAULT(/usr)
AM_MAINTAINER_MODE

dnl *************************************************************
dnl * Define the set of applicable options
dnl *************************************************************
AC_ARG_WITH(release,
	[AC_HELP_STRING([--with-release=XXX], [set release to XXX [1]])],
	RELEASE=$withval,
	RELEASE=1)
	AC_SUBST(RELEASE)
AC_ARG_WITH(statedir,
	[  --with-statedir=/foo    use state dir /foo [/var/lib/nfs]],
	statedir=$withval,
	statedir=/var/lib/nfs)
	AC_SUBST(statedir)
AC_ARG_WITH(statduser,
	[AC_HELP_STRING([--with-statduser=rpcuser],
                        [statd to run under @<:@rpcuser or nobody@:>@]
	)],
	statduser=$withval,
	if test "x$cross_compiling" = "xno"; then
		if grep -s '^rpcuser:' /etc/passwd > /dev/null; then
			statduser=rpcuser
		else
			statduser=nobody
		fi
	else
		statduser=nobody
	fi)
	AC_SUBST(statduser)
AC_ARG_WITH(start-statd,
	[AC_HELP_STRING([--with-start-statd=scriptname],
			[When an nfs filesystems is mounted with locking, run this script]
	)],
	startstatd=$withval,
	startstatd=/usr/sbin/start-statd
	)
	AC_SUBST(startstatd)
	AC_DEFINE_UNQUOTED(START_STATD, "$startstatd", [Define this to a script which can start statd on mount])
AC_ARG_ENABLE(nfsv3,
	[AC_HELP_STRING([--enable-nfsv3],
                        [enable support for NFSv3 @<:@default=yes@:>@])],
	enable_nfsv3=$enableval,
	enable_nfsv3=yes)
	if test "$enable_nfsv3" = yes; then
		AC_DEFINE(NFS3_SUPPORTED, 1, [Define this if you want NFSv3 support compiled in])
	else
		enable_nfsv3=
	fi
	AC_SUBST(enable_nfsv3)
AC_ARG_ENABLE(nfsv4,
	[AC_HELP_STRING([--enable-nfsv4],
                        [enable support for NFSv4 @<:@default=yes@:>@])],
	enable_nfsv4=$enableval,
	enable_nfsv4=yes)
	if test "$enable_nfsv4" = yes; then
		AC_DEFINE(NFS4_SUPPORTED, 1, [Define this if you want NFSv4 support compiled in])
		IDMAPD=idmapd
	else
		enable_nfsv4=
		IDMAPD=
	fi
	AC_SUBST(IDMAPD)
	AC_SUBST(enable_nfsv4)
	AM_CONDITIONAL(CONFIG_NFSV4, [test "$enable_nfsv4" = "yes"])
AC_ARG_ENABLE(gss,
	[AC_HELP_STRING([--enable-gss],
                        [enable support for rpcsec_gss @<:@default=yes@:>@])],
	enable_gss=$enableval,
	enable_gss=yes)
	if test "$enable_gss" = yes; then
		AC_DEFINE(GSS_SUPPORTED, 1, [Define this if you want rpcsec_gss support compiled in])
		GSSD=gssd
		SVCGSSD=svcgssd
	else
		enable_gss=
		GSSD=
		SVCGSSD=
	fi
	AC_SUBST(GSSD)
	AC_SUBST(SVCGSSD)
	AC_SUBST(enable_gss)
	AM_CONDITIONAL(CONFIG_GSS, [test "$enable_gss" = "yes"])
AC_ARG_ENABLE(kprefix,
	[AC_HELP_STRING([--enable-kprefix], [install progs as rpc.knfsd etc])],
	test "$enableval" = "yes" && kprefix=k,
	kprefix=)
	AC_SUBST(kprefix)
AC_ARG_ENABLE(secure-statd,
	[AC_HELP_STRING([--enable-secure-statd],
                        [Only lockd can use statd (security)])],
	test "$enableval" = "yes" && secure_statd=yes,
	secure_statd=yes)
	if test "$secure_statd" = yes; then
		AC_DEFINE(RESTRICTED_STATD, 1, [Define this if you want to enable various security checks in statd. These checks basically keep anyone but lockd from using this service.])
	fi
	AC_SUBST(secure_statd)
AC_ARG_ENABLE(rquotad,
	[AC_HELP_STRING([--enable-rquotad],
                        [enable rquotad @<:@default=yes@:>@])],
	enable_rquotad=$enableval,
	enable_rquotad=yes)
	if test "$enable_rquotad" = yes; then
		RQUOTAD=rquotad
	else
		RQUOTAD=
	fi
	AM_CONDITIONAL(CONFIG_RQUOTAD, [test "$enable_rquotad" = "yes"])
AC_ARG_WITH(rpcgen,
	[AC_HELP_STRING([--with-rpcgen=internal], [use internal rpcgen instead of system one])],
	rpcgen_path=$withval,
	rpcgen_path=yes )
	RPCGEN_PATH=
	if test "$rpcgen_path" == "yes"; then
	    for p in /usr/local/bin/rpcgen /usr/bin/rpcgen /bin/rpcgen
	    do if test -f $p ; then RPCGEN_PATH=$p ; break; fi ; done
	elif test "$rpcgen_path" != "internal"; then
	    RPCGEN_PATH=$rpcgen_path
	fi
	AC_SUBST(RPCGEN_PATH)
	AM_CONDITIONAL(CONFIG_RPCGEN, [test "$RPCGEN_PATH" == ""])
AC_ARG_ENABLE(uuid,
	[AC_HELP_STRING([--without-uuid], [Exclude uuid support and so avoid possibly buggy libblkid])],
	if test "$enableval" = "yes" ; then use_blkid=1; else use_blkid=0; fi,
	use_blkid=1)
	AC_DEFINE_UNQUOTED(USE_BLKID, $use_blkid, [Define if you want to use blkid to find uuid of filesystems])
AC_ARG_ENABLE(mount,
	[AC_HELP_STRING([--enable-mount],
			[Create mount.nfs and don't use the util-linux mount(8) functionality. @<:@default=no@:>@])],
	enable_mount=$enableval,
	enable_mount=yes)
	AM_CONDITIONAL(CONFIG_MOUNT, [test "$enable_mount" = "yes"])

# Check whether user wants TCP wrappers support
AC_TCP_WRAPPERS

# Arrange for large-file support
AC_SYS_LARGEFILE

AC_CONFIG_SRCDIR([support/include/config.h.in])
AC_CONFIG_HEADERS([support/include/config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_LIBTOOL
AM_PROG_CC_C_O

if test "x$cross_compiling" = "xno"; then
	CC_FOR_BUILD=${CC_FOR_BUILD-${CC-gcc}}
else
	CC_FOR_BUILD=${CC_FOR_BUILD-gcc}
fi

AC_SUBST(CC_FOR_BUILD)

AC_CHECK_TOOL(AR, ar)
AC_CHECK_TOOL(LD, ld)

AC_HEADER_STDC([])
AC_GNULIBC
AC_BSD_SIGNALS

dnl *************************************************************
dnl * Check for required libraries
dnl *************************************************************
AC_CHECK_FUNC(gethostbyname, , [AC_CHECK_LIB(nsl, gethostbyname, [LIBNSL="-lnsl"])])
AC_SUBST(LIBNSL)

AC_CHECK_FUNC(connect, ,
      AC_CHECK_LIB(socket, connect, [LIBSOCKET="-lsocket"],
                AC_MSG_ERROR(Function 'socket' not found.), $LIBNSL))

AC_CHECK_LIB(crypt, crypt, [LIBCRYPT="-lcrypt"])
if test "$enable_nfsv4" = yes; then
    AC_CHECK_LIB(event, event_dispatch, [libevent=1], AC_MSG_ERROR([libevent needed for nfsv4 support]))
    AC_CHECK_LIB(nfsidmap, nfs4_init_name_mapping, [libnfsidmap=1], AC_MSG_ERROR([libnfsidmap needed for nfsv4 support]))
    AC_CHECK_HEADERS(event.h, ,AC_MSG_ERROR([libevent needed for nfsv4 support]))
    AC_CHECK_HEADERS(nfsidmap.h, ,AC_MSG_ERROR([libnfsidmap needed for nfsv4 support]))
    dnl librpcsecgss already has a dependency on libgssapi,
    dnl but we need to make sure we get the right version
    if test "$enable_gss" = yes; then
     PKG_CHECK_MODULES(RPCSECGSS, librpcsecgss >= 0.10, ,
      [AC_MSG_ERROR([Unable to locate information required to use librpcsecgss.  If you have pkgconfig installed, you might try setting environment variable PKG_CONFIG_PATH to /usr/local/lib/pkgconfig])
      ]
     )
    PKG_CHECK_MODULES(GSSAPI, libgssapi >= 0.9)
    fi

fi
if test "$knfsd_cv_glibc2" = no; then
    AC_CHECK_LIB(bsd, daemon, [LIBBSD="-lbsd"])
fi
if test "$use_blkid" = 1; then
   AC_CHECK_LIB(blkid, blkid_get_cache, [LIBBLKID="-lblkid"], AC_MSG_ERROR([libblkid needed]))
   AC_CHECK_HEADER(blkid/blkid.h, , AC_MSG_ERROR([Cannot file libblkid header file blkid/blkid.h]))
fi
AC_SUBST(LIBSOCKET)
AC_SUBST(LIBCRYPT)
AC_SUBST(LIBBSD)
AC_SUBST(LIBBLKID)

if test "$enable_gss" = yes; then
  dnl 'gss' also depends on nfsidmap.h - at least for svcgssd_proc.c
  AC_CHECK_HEADERS(nfsidmap.h, ,AC_MSG_ERROR([libnfsidmap needed for gss support]))
  AC_CHECK_HEADERS(spkm3.h, ,AC_MSG_WARN([could not locate SPKM3 header; will not have SPKM3 support]))
  dnl the nfs4_set_debug function doesn't appear in all version of the library
  AC_CHECK_LIB(nfsidmap, nfs4_set_debug,
	       AC_DEFINE(HAVE_NFS4_SET_DEBUG,1,
			 [Whether nfs4_set_debug() is present in libnfsidmap]),)

  dnl Check for Kerberos V5
  AC_KERBEROS_V5

  dnl This is not done until here because we need to have KRBLIBS set
  dnl ("librpcsecgss=1" is so that it doesn't get added to LIBS)
  AC_CHECK_LIB(rpcsecgss, authgss_create_default, [librpcsecgss=1], AC_MSG_ERROR([librpcsecgss needed for nfsv4 support]), -lgssapi -ldl)
  AC_CHECK_LIB(rpcsecgss, authgss_set_debug_level,
  	       AC_DEFINE(HAVE_AUTHGSS_SET_DEBUG_LEVEL, 1, [Define this if the rpcsec_gss library has the function authgss_set_debug_level]),, -lgssapi -ldl)

fi

dnl *************************************************************
dnl Check for headers
dnl *************************************************************
AC_CHECK_HEADERS([arpa/inet.h fcntl.h libintl.h limits.h \
                 malloc.h memory.h netdb.h netinet/in.h paths.h \
                 stdlib.h string.h sys/file.h sys/ioctl.h sys/mount.h \
                 sys/param.h sys/socket.h sys/time.h sys/vfs.h \
                 syslog.h unistd.h com_err.h et/com_err.h \
                 ifaddrs.h])

dnl *************************************************************
dnl Checks for typedefs, structures, and compiler characteristics
dnl *************************************************************
AC_C_CONST
AC_TYPE_UID_T
AC_C_INLINE
AC_TYPE_OFF_T
AC_TYPE_PID_T
AC_TYPE_SIZE_T
AC_HEADER_TIME
AC_STRUCT_TM

dnl *************************************************************
dnl Check for functions
dnl *************************************************************
AC_FUNC_ALLOCA
AC_FUNC_CLOSEDIR_VOID
AC_FUNC_ERROR_AT_LINE
AC_FUNC_FORK
AC_FUNC_GETGROUPS
AC_FUNC_GETMNTENT
AC_PROG_GCC_TRADITIONAL
AC_FUNC_LSTAT
AC_FUNC_LSTAT_FOLLOWS_SLASHED_SYMLINK
AC_HEADER_MAJOR
#AC_FUNC_MALLOC
AC_FUNC_MEMCMP
#AC_FUNC_REALLOC
AC_FUNC_SELECT_ARGTYPES
AC_TYPE_SIGNAL
AC_FUNC_STAT
AC_FUNC_VPRINTF
AC_CHECK_FUNCS([alarm atexit dup2 fdatasync ftruncate getcwd \
               gethostbyaddr gethostbyname gethostname getmntent \
               gettimeofday hasmntopt inet_ntoa innetgr memset mkdir pathconf \
               realpath rmdir select socket strcasecmp strchr strdup \
               strerror strrchr strtol strtoul sigprocmask])


dnl *************************************************************
dnl Check for data sizes (XXX These should go away with libgssapi pkg-config)
dnl *************************************************************
AC_CHECK_SIZEOF(short)
AC_CHECK_SIZEOF(int)
AC_CHECK_SIZEOF(long)
AC_CHECK_SIZEOF(size_t)
AC_CHECK_SIZEOF(socklen_t)


dnl *************************************************************
dnl Export some path names to config.h
dnl *************************************************************
AC_DEFINE_UNQUOTED(NFS_STATEDIR, "$statedir", [This defines the location of the NFS state files. Warning: this must match definitions in config.mk!])

if test "x$cross_compiling" = "xno"; then
	CFLAGS_FOR_BUILD=${CFLAGS_FOR_BUILD-"$CFLAGS"}
	CXXFLAGS_FOR_BUILD=${CXXFLAGS_FOR_BUILD-"$CXXFLAGS"}
	CPPFLAGS_FOR_BUILD=${CPPFLAGS_FOR_BUILD-"$CPPFLAGS"}
	LDFLAGS_FOR_BUILD=${LDFLAGS_FOR_BUILD-"$LDFLAGS"}
else
	CFLAGS_FOR_BUILD=${CFLAGS_FOR_BUILD-""}
	CXXFLAGS_FOR_BUILD=${CXXFLAGS_FOR_BUILD-""}
	CPPFLAGS_FOR_BUILD=${CPPFLAGS_FOR_BUILD-""}
	LDFLAGS_FOR_BUILD=${LDFLAGS_FOR_BUILD-""}
fi

AC_SUBST(CFLAGS)
AC_SUBST(CXXFLAGS)
AC_SUBST(CPPFLAGS)
AC_SUBST(LDFLAGS)

AC_SUBST(CFLAGS_FOR_BUILD)
AC_SUBST(CXXFLAGS_FOR_BUILD)
AC_SUBST(CPPFLAGS_FOR_BUILD)
AC_SUBST(LDFLAGS_FOR_BUILD)

dnl *************************************************************
dnl Set up "global" CFLAGS
dnl *************************************************************
dnl Use architecture-specific compile flags
dnl (We use $host and not $build in case we are cross-compiling)
dnl *************************************************************
case $host in
  alpha*)
    ARCHFLAGS="-mno-fp-regs -ffixed-8" ;;
  *)
    ARCHFLAGS="" ;;
esac

my_am_cflags="-Wall $ARCHFLAGS -pipe"

AC_SUBST([AM_CPPFLAGS], ["-I\${top_srcdir}/support/include"])
AC_SUBST([AM_CFLAGS], ["$my_am_cflags"])

# Make sure that $ACLOCAL_FLAGS are used during a rebuild
AC_SUBST([ACLOCAL_AMFLAGS], ["-I $ac_macro_dir \$(ACLOCAL_FLAGS)"])

AC_CONFIG_FILES([
	Makefile
	linux-nfs/Makefile
	support/Makefile
	support/export/Makefile
	support/include/nfs/Makefile
	support/include/rpcsvc/Makefile
	support/include/sys/fs/Makefile
	support/include/sys/Makefile
	support/include/Makefile
	support/misc/Makefile
	support/nfs/Makefile
	tools/Makefile
	tools/locktest/Makefile
	tools/nlmtest/Makefile
	tools/rpcdebug/Makefile
	tools/rpcgen/Makefile
	utils/Makefile
	utils/exportfs/Makefile
	utils/gssd/Makefile
	utils/idmapd/Makefile
	utils/mount/Makefile
	utils/mountd/Makefile
	utils/nfsd/Makefile
	utils/nfsstat/Makefile
	utils/rquotad/Makefile
	utils/showmount/Makefile
	utils/statd/Makefile])
AC_OUTPUT
