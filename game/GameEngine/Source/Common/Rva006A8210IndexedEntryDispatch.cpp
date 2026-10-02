// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Retail 0x006A8210: dispatch the indexed 0x1c4-byte entry and, for index 2,
// seed the first two entries with the same value.

class Rva006A8210Entry
{
public:
	// The entry body at 0x006A8120 is Rva006A8210Entry::applyEntryList, defined
	// out of line in Rva006A8120IndexedEntryApply.cpp; the dispatcher only ever
	// reaches it through this pointer, never by name.
	void applyEntryList(int value, int index);
};

typedef void (Rva006A8210Entry::*Rva006A8210EntryCall)(int, int);

class Rva006A8210Owner
{
public:
	void dispatch(int value, int index);
};

void Rva006A8210Owner::dispatch(int value, int index)
{
	union
	{
		void *asVoid;
		Rva006A8210EntryCall asMember;
	} entryCallCast;
	entryCallCast.asMember = &Rva006A8210Entry::applyEntryList;
	((Rva006A8210Entry *)((char *)this + index * 0x1c4 + 0xb8)->*
		entryCallCast.asMember)(value, index);

	if (index == 2)
	{
		int i = 0;
		Rva006A8210Entry *entry = (Rva006A8210Entry *)((char *)this + 0xb8);
		for (; i < 3; ++i, entry = (Rva006A8210Entry *)((char *)entry + 0x1c4))
		{
			if (i != 2)
				(entry->*entryCallCast.asMember)(value, 2);
		}
	}
}
