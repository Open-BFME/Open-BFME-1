// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// A duplicate-this-string helper, 0x008543B0, 62 bytes.
//
// Plain strdup: measure, allocate, copy, and hand back NULL for a NULL input
// rather than faulting. It has no counterpart in the reference -- the callers
// there use AsciiString -- and the netcode reaches it from three places, all of
// them handing a C string across the GameSpy backend boundary where an
// AsciiString cannot go.
//
// The name is this tree's; retail carries no symbol for it. Both loops are
// MSVC's intrinsic strlen and strcpy expanded inline -- the length loop's
// lea/sub/inc shape is the giveaway -- so the only import is the allocation.

#include <string.h>

typedef unsigned int UnsignedInt;

extern "C" __declspec(dllimport) void *__cdecl malloc(unsigned int size);

char *BFMEDuplicateString(const char *str)
{
	if (str == 0) {
		return 0;
	}

	char *copy = (char *)malloc(strlen(str) + 1);
	if (copy != 0) {
		strcpy(copy, str);
	}

	return copy;
}
