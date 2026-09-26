/* MSVC 7.1 has no <strings.h>. nbench1.c (nbench-byte 2.2.3) includes it
   only for bzero(); this shim is a local compatibility header, not part of
   the upstream tarball. See PROVENANCE.md. */
#ifndef OPEN_BFME_NBENCH_STRINGS_H
#define OPEN_BFME_NBENCH_STRINGS_H
#include <string.h>
#ifdef _MSC_VER
#define bzero(p, n) memset((p), 0, (n))
#endif
#endif
