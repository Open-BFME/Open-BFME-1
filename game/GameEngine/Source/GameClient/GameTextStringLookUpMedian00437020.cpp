// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
//
// Address-derived reconstruction of the 205-byte StringLookUp median helper
// at retail RVA 0x00437020.  Gen004388C0 reaches this body through its
// 0x00038b13 thunk; the caller chain continues through the named
// GameTextManager::initMapStringFile entry at 0x00438d50.  That entry builds
// eight-byte StringLookUp records (AsciiString *label, StringInfo *info).
// The owning template specialization is not named by the available symbols.
//
// The first three comparison sites use the authentic MSVCR71 _stricmp import
// at VA 0x0135933c.  The two later record comparisons call the already-owned
// compareStringLookUpLess body at 0x004367f0.  The declaration-only member
// below preserves retail's thiscall argument materialization; its linker alias
// routes it to that proven stdcall body, so this TU introduces no comparator
// duplicate or unproven function identity.

extern const char g_bfmeEmptyAscii[];
extern "C" __declspec(dllimport) int __cdecl _stricmp(
	const char *left, const char *right);

class GameTextAsciiString00437020
{
public:
	__forceinline const char *str() const
	{
		return m_data ? (const char *)m_data + 8 : g_bfmeEmptyAscii;
	}

private:
	void *m_data;
};

struct GameTextStringLookUp00437020
{
	GameTextAsciiString00437020 *label;
	void *info;
};

struct GameTextStringCompare00437020
{
	void *state;
	bool operator()(const void *, const void *) const;
};

#pragma comment(linker, "/alternatename:??RGameTextStringCompare00437020@@QBE_NPBX0@Z=?compareStringLookUpLess@@YG_NPBX0@Z")

namespace _STL
{

template <class Tp, class Compare>
const Tp &game_text_median(const Tp &a, const Tp &b, const Tp &c,
	Compare comp)
{
	if (_stricmp(a.label->str(), b.label->str()) < 0)
		if (_stricmp(b.label->str(), c.label->str()) < 0)
			return b;
		else if (comp((const void *)&a, (const void *)&c))
			return c;
		else
			return a;
	else if (_stricmp(a.label->str(), c.label->str()) < 0)
		return a;
	else if (comp((const void *)&b, (const void *)&c))
		return c;
	else
		return b;
}

template const GameTextStringLookUp00437020 &game_text_median<
	GameTextStringLookUp00437020, GameTextStringCompare00437020>(
	const GameTextStringLookUp00437020 &,
	const GameTextStringLookUp00437020 &,
	const GameTextStringLookUp00437020 &,
	GameTextStringCompare00437020);

}
