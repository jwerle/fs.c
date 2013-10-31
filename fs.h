
#ifndef __FS_H__
#define __FS_H__ 1


/**
 * fs.h
 *
 * copyright 2013 - joseph werle <joseph.werle@gmail.com>
 */


#include <sys/stat.h>

typedef struct stat fs_stats;



/**
 * Prints the last error to stderr
 */

void
fs_error (char *prefix);


/**
 * Opens a file with given flags
 * and returns a file descriptor
 */

FILE *
fs_open (char *path, char *flags);


/**
 * Closes a given file descriptor
 */

int
fs_close (FILE *file);


/**
 * Moves a path to a new destination
 */

int
fs_rename (char *from, char *to);


/**
 * Stats a given path and returns
 * a `struct stat`
 */

fs_stats *
fs_stat (char *path);


/**
 * Stats a given file descriptor
 */

fs_stats *
fs_fstat (FILE *file);


/**
 * Stats a given link path
 */

fs_stats *
fs_lstat (char *path);


/**
 * Truncates a file to a specified
 * length from a given file descriptor
 */

int
fs_ftruncate (FILE *file, int len);


/**
 * Truncates a file to a specified
 * len from a given file path
 */

int
fs_truncate (char *path, int len);


/**
 * Changes ownership of a given
 * file path to a given owner
 * and group
 */

int
fs_chown (char *path, int uid, int gid);


/**
 * Change ownership of a given
 * file descriptor to a given owner
 * and group
 */

int
fs_fchown (FILE *file, int uid, int gid);


/**
 * Returns the size of a file from
 * a given file path
 */

size_t
fs_size (char *path);


/**
 * Returns the size of a file
 * from a given file descriptor
 */

size_t
fs_fsize (FILE *file);


/**
 * Change ownership of a given
 * link path to a given owner
 * and group
 */

int
fs_lchown (char *path, int uid, int gid);


/**
 * Reads a file by a given file
 * path
 */

char *
fs_read (char *path);


/**
 * Reads a file by a given
 * file path by a given `n`
 * number of bytes
 */

char *
fs_nread (char *path, int len);


/**
 * Reads a file by a given
 * file descriptor
 */

char *
fs_fread (FILE *file);


/**
 * Reads a file by a given
 * file descriptor by a given
 * `n` number of bytes
 */

char *
fs_fnread (FILE *file, int len);


/**
 * Writes a buffer
 * to a given file path
 */

int
fs_write (char *path, char *buffer);


/**
 * Writes `n` bytes of a buffer to a given
 * file path
 */

int
fs_nwrite (char *path, char *buffer, int len);


/**
 * Writes a buffer to a given
 * file stream
 */

int
fs_fwrite (FILE *file, char *buffer);


/**
 * Writes `n` bytes of a buffer
 * to a given file stream
 */

int
fs_fnwrite (FILE *file, char *buffer, int len);


/**
 * Makes a directory and returns 0
 * on success or -1 on failure
 */

int
fs_mkdir (char *path, int mode);


/**
 * Removes a directory and returns
 * 0 on success and -1 on failure
 */

int
fs_rmdir (char *path);

/**
 * Check if the given `path` exists
 */

int
fs_exists (char *path);


#endif
