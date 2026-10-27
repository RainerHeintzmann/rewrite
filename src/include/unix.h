#ifndef UNIX_H
#define UNIX_H

/* 2026: the old BSD names (bcopy, index, ...) are no longer used; their
   macros broke the declarations of <string.h> on Linux (glibc) */
#include <stdlib.h>
#include <string.h>

#endif /* UNIX_H */
