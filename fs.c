/**
 * fs.c
 *
 * copyright 2013 - joseph werle <joseph.werle@gmail.com>
 */

#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>


#include "fs.h"


void
fs_error (char *prefix) {
  char fmt[256];
  sprintf(fmt, "fs: %s: error", prefix);
  perror(fmt);
}


FILE *
fs_open (char *path, char *flags) {
  return fopen(path, flags);
}


int
fs_close (FILE *file) {
  return fclose(file);
}


int
fs_rename (char *from, char *to) {
  return rename(from, to);
}


fs_stats *
fs_stat (char *path) {
  fs_stats *stats = malloc(sizeof(fs_stats));
  int e = stat(path, stats);
  if (-1 == e) return NULL;
  else return stats;
}


fs_stats *
fs_fstat (FILE *file) {
  fs_stats *stats = malloc(sizeof(fs_stats));
  int fd = fileno(file);
  int e = fstat(fd, stats);
  if (-1 == e) return NULL;
  else return stats;
}


fs_stats *
fs_lstat (char *path) {
  fs_stats *stats = malloc(sizeof(fs_stats));
  int e = lstat(path, stats);
  if (-1 ==e) return NULL;
  else return stats;
}


int
fs_ftruncate (FILE *file, int len) {
  int fd = fileno(file);
  return ftruncate(fd, (off_t) len);
}


int
fs_truncate (char *path, int len) {
  return truncate(path, (off_t) len);
}


int
fs_chown (char *path, int uid, int gid) {
  return chown(path, (uid_t) uid, (gid_t) gid);
}


int
fs_fchown (FILE *file, int uid, int gid) {
  int fd = fileno(file);
  return fchown(fd, (uid_t) uid, (gid_t) gid);
}


int
fs_lchown (char *path, int uid, int gid) {
  return lchown(path, (uid_t) uid, (gid_t) gid);
}


size_t
fs_size (char *path) {
  size_t size;
  FILE *file = fs_open(path, "r");
  if (NULL == file) return -1;
  fseek(file, 0, SEEK_END);
  size = ftell(file);
  fs_close(file);
  return size;
}


size_t
fs_fsize (FILE *file) {
  // store current position
  unsigned long pos = ftell(file);
  rewind(file);
  fseek(file, 0, SEEK_END);
  size_t size = ftell(file);
  fseek(file, pos, SEEK_SET);
  return size;
}


char *
fs_read (char *path) {
  FILE *file = fs_open(path, "r");
  if (NULL == file) return NULL;
  char *data = fs_fread(file);
  fclose(file);
  return data;
}


char *
fs_nread (char *path, int len) {
  FILE *file = fs_open(path, "r");
  if (NULL == file) return NULL;
  char *buffer = fs_fnread(file, len);
  fs_close(file);
  return buffer;
}


char *
fs_fread (FILE *file) {
  size_t fsize = fs_fsize(file);
  return fs_fnread(file, fsize);
}


char *
fs_fnread (FILE *file, int len) {
  char *buffer = malloc(sizeof(char) * len);
  fread(buffer, 1, len, file);
  buffer[len -1] = '\0';
  return buffer;
}


int
fs_write (char *path, char *buffer) {
  return fs_nwrite(path, buffer, strlen(buffer));
}


int
fs_nwrite (char *path, char *buffer, int len) {
  FILE *file = fs_open(path, "w");
  if (NULL == file) return -1;
  int result = fs_fnwrite(file, buffer, len);
  fclose(file);
  return result;
}


int
fs_fwrite (FILE *file, char *buffer) {
  return fs_fnwrite(file, buffer, strlen(buffer));
}


int
fs_fnwrite (FILE *file, char *buffer, int len) {
  return (int) fwrite(buffer, 1, len, file);
}


int
fs_mkdir (char *path, int mode) {
  return mkdir(path, (mode_t) mode);
}


int
fs_rmdir (char *path) {
  return rmdir(path);
}


int
fs_exists (char *path) {
  struct stat b;
  return stat(path, &b);
}
