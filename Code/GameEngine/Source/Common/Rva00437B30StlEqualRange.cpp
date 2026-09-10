// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB
// stlport

// Retail 0x00437B30 is STLport 4.5.3 __equal_range over eight-byte
// GameTextStringLookUp records.  The matched caller at 0x00437E50 supplies
// the hidden pair-return storage followed by first, last, value, comparator,
// and the unused distance pointer.  The owner remains address-derived: the
// caller proves this ABI and the lower/upper callees, not a game-class name.

extern const char Rva006A16B0Empty[];
extern "C" __declspec(dllimport) int __cdecl _strcmpi(
	const char *left, const char *right);

struct GameTextAsciiString
{
	void *m_data;

	const char *str() const
	{
		return m_data ? (const char *)m_data + 8 : Rva006A16B0Empty;
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

extern GameTextStringLookUp *__cdecl GameTextLowerBound004371E0(
	GameTextStringLookUp *first, GameTextStringLookUp *last,
	const char *const &value, GameTextStringCompare comp, int *distance);
extern GameTextStringLookUp *__cdecl GameTextUpperBound00437260(
	GameTextStringLookUp *first, GameTextStringLookUp *last,
	const char *const &value, GameTextStringCompare comp, int *distance);

namespace _STL
{
	template <class T1, class T2>
	struct pair
	{
		T1 first;
		T2 second;
		pair(const T1 &a, const T2 &b) : first(a), second(b) {}
	};
}

_STL::pair<GameTextStringLookUp *, GameTextStringLookUp *> Rva00437B30EqualRange(
	GameTextStringLookUp *first, GameTextStringLookUp *last,
	const char *const &value, GameTextStringCompare comp, int *distance)
{
	int length = last - first;
	if (length > 0)
	{
		for (;;)
		{
			const char *key = value;
			int half = length >> 1;
			GameTextStringLookUp *middle = first + half;
			if (_strcmpi(middle->label->str(), key) < 0)
			{
				first = middle + 1;
				length = length - half - 1;
			}
			else
			{
				const char *secondKey = value;
				if (_strcmpi(secondKey, middle->label->str()) < 0)
				{
					length = half;
				}
				else
				{
					GameTextStringLookUp *left =
						GameTextLowerBound004371E0(
							first, middle, value, comp, 0);
					GameTextStringLookUp *right =
						GameTextUpperBound00437260(
							middle + 1, first + length, value, comp, 0);
					return _STL::pair<GameTextStringLookUp *, GameTextStringLookUp *>(
						left, right);
				}
			}
			if (length <= 0)
				break;
		}
	}
	return _STL::pair<GameTextStringLookUp *, GameTextStringLookUp *>(
		first, first);
}
