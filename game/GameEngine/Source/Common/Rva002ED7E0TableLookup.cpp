// Retail 0x002ED7E0, 74 bytes.  Find the first registered entry accepted by
// the shared callback.

typedef int (__cdecl *Rva002ED7E0Lookup)(void *entry, void *key);

// The slot is MSVCR71's _strcmpi import (VA 0x0135933C).
extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *, const char *);
// Retail VA 0x012AA008, 24 bytes: null-terminated side-name table
// (ROHAN, GONDOR, MORDOR, ISENGARD, NEUTRAL, 0) read by the lookup below.
void *g_012AA008[] = {
	(void *)"ROHAN", (void *)"GONDOR", (void *)"MORDOR",
	(void *)"ISENGARD", (void *)"NEUTRAL", 0
};

#define Rva002ED7E0LookupSlot ((Rva002ED7E0Lookup)_strcmpi)

int __cdecl rva002ed7e0Find(void *key)
{
	if (key == 0)
		return 4;

	Rva002ED7E0Lookup lookup = Rva002ED7E0LookupSlot;
	void **entries = g_012AA008;
	int index = 0;
	for (; entries != 0; ++entries, ++index)
	{
		void *entry = *entries;
		if (entry == 0)
			return 4;
		if (lookup(entry, key) == 0)
			return index;
	}
	return 4;
}
