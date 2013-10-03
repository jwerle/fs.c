
#include "fs.h"
#include <assert.h>

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
 * close
 * open
 * utimes
 * futimes
 * fsync
 * write
 * read
 * readFile
 * writeFile
 * appendFile
 * watchFile
 * unwatchFile
 * watch
 * exists
 */


char *alpha = "abcdefghijklmnopqrstuvwxyz";

int
main (int argc, char *argv[]) {
  int rc, i = 0;
  FILE *fd;

  fd = fs_open("./tmp/file", "rw");

  assert(fd);

  // just to be sure ;)
  assert(26 == strlen(alpha));

  assert(fs_stat("./tmp"));
  assert(fs_lstat("./tmp/file.link"));
  assert(fs_fstat(fd));

  char *buf = fs_fread(fd);
  assert(0 == strcmp(alpha, buf));
  assert(0 == strcmp(fs_read("./tmp/file"), buf));
  assert(0 == strcmp(fs_read("./tmp/file.link"), fs_read("./tmp/file")));

  assert(strlen(alpha) == strlen(buf));

  for (; i < strlen(alpha); ++i) {
    assert(alpha[i] == buf[i]);
  }

  rc = fs_rename("./tmp", "./tmp.bak");

  assert(0 == rc);
  assert(fs_stat("./tmp.bak"));

  rc = fs_rename("./tmp.bak", "./tmp");
  assert(0 == rc);


  return 0;
}
