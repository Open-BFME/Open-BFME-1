// Retail 0x002ED7E0, 74 bytes.  Find the first registered entry accepted by
// the shared callback.

typedef int (__cdecl *Rva002ED7E0Lookup)(void *entry, void *key);

#define Rva002ED7E0LookupSlot (*(Rva002ED7E0Lookup *)0x0135933C)

int __cdecl rva002ed7e0Find(void *key)
{
	if (key == 0)
		return 4;

	Rva002ED7E0Lookup lookup = Rva002ED7E0LookupSlot;
	void **entries = (void **)0x012AA008;
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
