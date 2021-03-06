/* mountpoint.c - Check if a directory is a mountpoint.
 *
 * Copyright 2012 Elie De Brauwer <eliedebrauwer@gmail.com>

USE_MOUNTPOINT(NEWTOY(mountpoint, "<1qdx", TOYFLAG_BIN))

config MOUNTPOINT
  bool "mountpoint"
  default y
  help
    usage: mountpoint [-q] [-d] directory
           mountpoint [-q] [-x] device

    -q	Be quiet, return zero if directory is a mountpoint
    -d	Print major/minor device number of the directory
    -x	Print major/minor device number of the block device
*/

#define FOR_mountpoint
#include "toys.h"

void mountpoint_main(void)
{
  struct stat st1, st2;
  int res = 0;
  int quiet = toys.optflags & FLAG_q;
  toys.exitval = 1; // be pessimistic
  strncpy(toybuf, toys.optargs[0], sizeof(toybuf));
  if (((toys.optflags & FLAG_x) && lstat(toybuf, &st1)) || stat(toybuf, &st1))
    perror_exit("%s", toybuf);

  if (toys.optflags & FLAG_x){
    if (S_ISBLK(st1.st_mode)) {
      if (!quiet) printf("%u:%u\n", major(st1.st_rdev), minor(st1.st_rdev));
      toys.exitval = 0;
      return;
    }
    if (!quiet) printf("%s: not a block device\n", toybuf);
    return;
  }

  if(!S_ISDIR(st1.st_mode)){
    if (!quiet) printf("%s: not a directory\n", toybuf);
    return;
  }
  strncat(toybuf, "/..", sizeof(toybuf));
  stat(toybuf, &st2);
  res = (st1.st_dev != st2.st_dev) ||
    (st1.st_dev == st2.st_dev && st1.st_ino == st2.st_ino);
  if (!quiet) printf("%s is %sa mountpoint\n", toys.optargs[0], res ? "" : "not ");
  if (toys.optflags & FLAG_d)
    printf("%u:%u\n", major(st1.st_dev), minor(st1.st_dev));
  toys.exitval = res ? 0 : 1;
}
