// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// STLport insertion-sort driver for BFME's StringLookUp records; calls the
// already-landed GameTextLinearInsert00437C80 for each element past the first.

struct GameTextAsciiString
{
	void *m_data;
};

struct GameTextStringLookUp
{
	GameTextAsciiString *label;
	void *info;
};

struct GameTextStringCompare
{
	void *state;
};

void __cdecl GameTextLinearInsert00437C80(
	GameTextStringLookUp *first, GameTextStringLookUp *last,
	GameTextAsciiString *label, void *info, GameTextStringCompare comp);

void __cdecl GameTextInsertionSort00437E90(
	GameTextStringLookUp *first, GameTextStringLookUp *last,
	GameTextStringCompare comp)
{
	if (first == last)
		return;
	GameTextStringLookUp *mid = first + 1;
	if (mid == last)
		return;
	for (GameTextStringLookUp *i = mid; i != last; ++i)
	{
		GameTextLinearInsert00437C80(first, i, i->label, i->info, comp);
	}
}
