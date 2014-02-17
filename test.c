
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // unlink
#include <string.h>
#include <time.h>
#include "fs.h"

#define TEST(name) \
  static void test_##name(void)

#define RUN_TEST(test) \
  test_count++; \
  test_##test(); \
  puts("  \e[92m✓ \e[90m" #test "\e[0m");

static int test_count = 0;
static char *alpha = "abcdefghijklmnopqrstuvwxyz\n";

TEST (fs_open) {
  FILE *fd;

  fd = fs_open("./tmp/file", FS_OPEN_READWRITE);
  assert(fd);
  fs_close(fd);

  fd = fs_open("/root/foo", FS_OPEN_WRITE);
  assert(NULL == fd);
}

TEST (fs_close) {
  FILE *fd = fs_open("./tmp/file", FS_OPEN_READWRITE);
  assert(0 == fs_close(fd));
}

TEST (fs_mkdir) {
  fs_rmdir("./tmp/dir");
  fs_mkdir("./tmp/dir", 0777);
  assert(0 == fs_exists("./tmp/dir"));
  fs_rmdir("./tmp/dir");
}

TEST (fs_exists) {
  assert(0 == fs_exists("./tmp/file"));
  assert(0 == fs_exists("./tmp/file.link"));
  assert(-1 == fs_exists("./tmp/a file that doesn't exist"));
}

TEST (fs_stat) {
  fs_stats *s;
  s = fs_stat("./tmp/file");
  assert(s);
  free(s);
  assert(NULL == fs_stat("./tmp/a file that doesn't exist"));
}

TEST (fs_fstat) {
  FILE *fd = fs_open("./tmp/file", FS_OPEN_READ);
  assert(fd);

  fs_stats *s = fs_fstat(fd);
  assert(s);
  free(s);

  assert(NULL == fs_fstat(NULL));
  fs_close(fd);
}

TEST (fs_lstat) {
  fs_stats *s = fs_lstat("./tmp/file.link");
  assert(s);
  free(s);
}

TEST (fs_truncate) {
  fs_write("./tmp/alpha", alpha);
  assert(0 == fs_truncate("./tmp/alpha", 9));
  char *buf = fs_read("./tmp/alpha");
  assert(0 == strcmp(buf, "abcdefghi"));
  free(buf);
}

TEST (fs_read) {
#ifndef _WIN32
  char *f1 = fs_read("./tmp/file");
  char *f2 = fs_read("./tmp/file.link");
  assert(0 == strcmp(f1, f2));
  free(f1);
  free(f2);

  // GH-14
  fs_write("./tmp/alpha", alpha);
  char *buf = fs_read("./tmp/alpha");
  assert(0 == strcmp(alpha, buf));
  free(buf);
#endif
}

TEST (fs_nread) {
  fs_write("./tmp/alpha", alpha);
  char *buf = fs_nread("./tmp/alpha", 9);
  assert(0 == strcmp(buf, "abcdefghi"));
  free(buf);
}

TEST (fs_fread) {
  fs_write("./tmp/alpha", alpha);
  FILE *fd = fs_open("./tmp/alpha", FS_OPEN_READ);
  assert(fd);
  char *buf = fs_fread(fd);
  assert(0 == strcmp(alpha, buf));
  free(buf);
  fs_close(fd);
}

TEST (fs_rename) {
  fs_write("./tmp/alpha", alpha);
  assert(0 == fs_rename("./tmp/alpha", "./tmp/foo"));
  assert(-1 == fs_exists("./tmp/alpha"));
  char *buf = fs_read("./tmp/foo");
  assert(0 == strcmp(alpha, buf));
  free(buf);
  unlink("./tmp/foo");
}

TEST (fs_rmdir) {
  assert(0 == fs_mkdir("./tmp/dir", 0777));
  assert(0 == fs_rmdir("./tmp/dir"));
  assert(-1 == fs_exists("./tmp/dir"));
}

TEST (fs_write) {
  assert(fs_write("./tmp/alpha", alpha));
  char *buf = fs_read("./tmp/alpha");
  assert(0 == strcmp(alpha, buf));
  free(buf);
}

TEST (fs_nwrite) {
  assert(fs_nwrite("./tmp/alpha", alpha, 9));
  char *buf = fs_read("./tmp/alpha");
  assert(0 == strcmp(buf, "abcdefghi"));
  free(buf);
}

TEST (fs_fwrite) {
  FILE *fd = fs_open("./tmp/alpha", FS_OPEN_WRITE);
  assert(fd);
  fs_fwrite(fd, alpha);
  fs_close(fd);

  char *buf = fs_read("./tmp/alpha");
  printf("-%s-\n", buf);
  assert(0 == strcmp(buf, alpha));
  free(buf);
}

TEST (fs_fnwrite) {
  FILE *fd = fs_open("./tmp/alpha", FS_OPEN_WRITE);
  assert(fd);
  fs_fnwrite(fd, alpha, 9);
  fs_close(fd);

  char *buf = fs_read("./tmp/alpha");
  assert(0 == strcmp(buf, "abcdefghi"));
  free(buf);
}



/**
 * -rename
 * -ftruncate
 * -truncate
 * -chown
 * -fchown
 * -lchown
 * chmod
 * fchmod
 * lchmod
 * -stat
 * -fstat
 * -lstat
 * link
 * symlink
 * readlink
 * realpath
 * unlink
 * rmdir
 * mkdir
 * readdir
 * -close
 * -open
 * utimes
 * futimes
 * fsync
 * write
 * -read
 * -readFile
 * writeFile
 * appendFile
 * watchFile
 * unwatchFile
 * watch
 * exists
 */


int
main () {
  clock_t start = clock();

  printf("\n");

  RUN_TEST(fs_open);
  RUN_TEST(fs_close);
  RUN_TEST(fs_mkdir);
  RUN_TEST(fs_exists);
  RUN_TEST(fs_stat);
  RUN_TEST(fs_fstat);
  RUN_TEST(fs_lstat);
  RUN_TEST(fs_truncate);
  RUN_TEST(fs_read);
  RUN_TEST(fs_nread);
  RUN_TEST(fs_fread);
  RUN_TEST(fs_rename);
  RUN_TEST(fs_rmdir);
  RUN_TEST(fs_write);
  RUN_TEST(fs_nwrite);
  RUN_TEST(fs_fwrite);
  RUN_TEST(fs_fnwrite);

  printf("\n  \e[90m%d tests passed in \e[32m%.5fs\e[0m\n\n"
    , test_count
    , (float) (clock() - start) / CLOCKS_PER_SEC);

  return 0;
}
