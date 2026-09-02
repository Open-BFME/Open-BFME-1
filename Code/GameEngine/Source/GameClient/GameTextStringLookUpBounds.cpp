// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// STLport lower/upper bound passes for BFME's eight-byte StringLookUp records.

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

GameTextStringLookUp *__cdecl GameTextLowerBound004371E0(
	GameTextStringLookUp *first, GameTextStringLookUp *last,
	const char *const &value, GameTextStringCompare comp, int *distance)
{
	int length = last - first;
	while (length > 0)
	{
		const char *needle = value;
		int half = length >> 1;
		GameTextStringLookUp *middle = first + half;
		if (_strcmpi(middle->label->str(), needle) < 0)
		{
			first = middle + 1;
			length -= half + 1;
		}
		else
		{
			length = half;
		}
	}
	return first;
}

GameTextStringLookUp *__cdecl GameTextUpperBound00437260(
	GameTextStringLookUp *first, GameTextStringLookUp *last,
	const char *const &value, GameTextStringCompare comp, int *distance)
{
	int length = last - first;
	while (length > 0)
	{
		const char *needle = value;
		int half = length >> 1;
		GameTextStringLookUp *middle = first + half;
		if (_strcmpi(needle, middle->label->str()) < 0)
		{
			length = half;
		}
		else
		{
			first = middle + 1;
			length -= half + 1;
		}
	}
	return first;
}
