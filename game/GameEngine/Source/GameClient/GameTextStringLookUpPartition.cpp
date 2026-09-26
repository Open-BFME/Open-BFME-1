// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// STLport unguarded partition for BFME's StringLookUp records.

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

GameTextStringLookUp *__cdecl GameTextPartition00437120(
	GameTextStringLookUp *first, GameTextStringLookUp *last,
	GameTextAsciiString *pivot, GameTextStringCompare comp)
{
	for (;;)
	{
		while (_strcmpi(first->label->str(), pivot->str()) < 0)
			++first;

		--last;
		while (_strcmpi(pivot->str(), last->label->str()) < 0)
			--last;

		if (first >= last)
			return first;

		GameTextStringLookUp temporary = *first;
		*first = *last;
		*last = temporary;
		++first;
	}
}
