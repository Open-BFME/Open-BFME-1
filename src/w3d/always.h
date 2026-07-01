// Minimal stand-in for WWLib always.h. Provides the guard, assert (compiled out
// by // cl: /DNDEBUG to match retail), and NULL; the real header is W3D config/
// memory-pool machinery no ported file touches. Extend loudly when needed.
#ifndef ALWAYS_H
#define ALWAYS_H

#include <assert.h>

#ifndef	NULL
	#define	NULL		0
#endif

#endif
