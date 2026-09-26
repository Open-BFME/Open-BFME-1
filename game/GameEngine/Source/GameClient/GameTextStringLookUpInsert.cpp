// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// STLport unguarded linear insert for BFME's StringLookUp records.

extern const char g_bfmeEmptyAscii[];
extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *left, const char *right);

struct GameTextAsciiString
{
	void *m_data;
	const char *str() const
	{
		return m_data ? (const char *)m_data + 8 : g_bfmeEmptyAscii;
	}
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

void __cdecl GameTextUnguardedLinearInsert004372E0(
	GameTextStringLookUp *hole, GameTextAsciiString *label, void *info,
	GameTextStringCompare comp)
{
	GameTextStringLookUp *previous = hole - 1;
	while (_strcmpi(label->str(), previous->label->str()) < 0)
	{
		*hole = *previous;
		hole = previous;
		--previous;
	}
	hole->label = label;
	hole->info = info;
}

void __cdecl GameTextLinearInsert00437C80(
	GameTextStringLookUp *first, GameTextStringLookUp *last,
	GameTextAsciiString *label, void *info, GameTextStringCompare comp)
{
	if (_strcmpi(label->str(), first->label->str()) < 0)
	{
		GameTextStringLookUp *destination = last + 1;
		int count = last - first;
		if (count > 0)
		{
			GameTextStringLookUp *source = destination - 1;
			do
			{
				--source;
				--destination;
				*destination = *source;
			}
			while (--count);
		}
		first->label = label;
		first->info = info;
	}
	else
	{
		GameTextUnguardedLinearInsert004372E0(last, label, info, comp);
	}
}
