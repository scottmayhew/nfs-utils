// SPDX-License-Identifier: GPL-2.0-or-later
/* Helpers for fd-based mounting.
 *
 * Based on test-fsmount.c:
 * Copyright (C) 2017 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */
#ifndef _NFS_UTILS_MOUNT_FSCONTEXT_H
#define _NFS_UTILS_MOUNT_FSCONTEXT_H

#define E(x) do { if ((x) == -1) { perror(#x); exit(1); } } while(0)

extern char *progname;

static void check_messages(int fd)
{
	char buf[4096];
	int err, n;

	err = errno;

	for (;;) {
		n = read(fd, buf, sizeof(buf));
		if (n < 0)
			break;
		n -= 2;

		switch (buf[0]) {
		case 'e':
			nfs_error(_("%s: Error: %*.*s"), progname, n, n, buf + 2);
			break;
		case 'w':
			nfs_error(_("%s: Warning: %*.*s"), progname, n, n, buf + 2);
			break;
		case 'i':
			nfs_error(_("%s: Info: %*.*s"), progname, n, n, buf + 2);
			break;
		}
	}

	errno = err;
}

static int fsctx_mount_error(int fd, const char *s)
{
	check_messages(fd);
	nfs_error(_("%s: %s: %m"), progname, s);
	return 0;
}

/* Hope -1 isn't a syscall */
#ifndef __NR_fsopen
#define __NR_fsopen -1
#endif
#ifndef __NR_fsmount
#define __NR_fsmount -1
#endif
#ifndef __NR_fsconfig
#define __NR_fsconfig -1
#endif
#ifndef __NR_move_mount
#define __NR_move_mount -1
#endif


static inline int fsopen(const char *fs_name, unsigned int flags)
{
	return syscall(__NR_fsopen, fs_name, flags);
}

static inline int fsmount(int fsfd, unsigned int flags, unsigned int ms_flags)
{
	return syscall(__NR_fsmount, fsfd, flags, ms_flags);
}

static inline int fsconfig(int fsfd, unsigned int cmd,
			   const char *key, const void *val, int aux)
{
	return syscall(__NR_fsconfig, fsfd, cmd, key, val, aux);
}

static inline int move_mount(int from_dfd, const char *from_pathname,
			     int to_dfd, const char *to_pathname,
			     unsigned int flags)
{
	return syscall(__NR_move_mount,
		       from_dfd, from_pathname,
		       to_dfd, to_pathname, flags);
}

static inline int fspick(int dirfd, const char *pathname, unsigned int flags)
{
	return syscall(__NR_fspick, dirfd, pathname, flags);
}

#define E_fsconfig(fd, cmd, key, val, aux)				\
	do {								\
		if (fsconfig(fd, cmd, key, val, aux) == -1)		\
			return fsctx_mount_error(fd, key ?: "create");	\
	} while (0)

#endif

/* _NFS_UTILS_MOUNT_FSCONTEXT_H */
