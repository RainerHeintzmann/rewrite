#ifndef UNIX_H
#define UNIX_H

#define bcopy(s, d, n) memcpy((d), (s), (n))
#define bzero(s, n)    memset((s), 0, (n))
#define bcmp(a, b, n)  memcmp((a), (b), (n))

#define index(s, c)    strchr((s), (c))
#define rindex(s, c)   strrchr((s), (c))

#include <stdlib.h>  /* mktemp, alloca: use the system declarations */
#include <string.h>

#endif /* UNIX_H */
