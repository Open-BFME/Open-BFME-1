// ?d_0036ef70Method@Rva0036EF70Owner@@QAE?AW4NameKeyType@@XZ
// partial score=0.54 date=2026-09-21
// ?d_0036ef70@@YAXXZ
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Address-derived method; the retail owner class is unknown, so the owner,
// its +0x4/+0x8 fields and the Player/map-value field offsets keep the
// address token.  Computes a NameKeyType from the literal "kq"; if a live
// Object* at +0x8 has a controlling Player, recomputes the key from the
// Player's AsciiString-shaped field at +0x28 (inlined NAMEKEY expansion --
// matches NameKeyHelperThunk.cpp's NAMEKEY(AsciiString) body) and looks that
// key up in a std::map<int,AsciiString> hanging off +0x6c of the +0x4
// field (found via the STLport int-keyed find() alias in PeerDefs.cpp,
// dup_0036e040); on a hit the found string's own key (via a real call to
// NAMEKEY(), not inlined) overrides the "kq" default.

#include <map>

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *s);
};

// DIR32: TheNameKeyGenerator
extern NameKeyGenerator *g_theNameKeyGenerator;	// @0x012ED600
extern "C" char g_NAMEKEY_empty_string;			// @0x0107388B, NAMEKEY empty string literal

// Minimal POD layout matching NameKeyHelperThunk.cpp's NAMEKEY(const AsciiString &)
// parameter -- only used to call into that already-linked free function.
class AsciiStringData;
class AsciiString
{
public:
	AsciiStringData *m_data;
};
NameKeyType NAMEKEY(const AsciiString &s);	// ?NAMEKEY@@YA?AW4NameKeyType@@ABVAsciiString@@@Z

// Retail's copy ctor call is the same ICF-shared StringBase<char> private
// copy ctor Bfme5MatPassCtors.cpp documents (0x00887B60); the trailing
// releaseBuffer() calls are StringBase<char>::releaseBuffer (0x00887940),
// both already defined out of line in StringBase.cpp.
template <typename Char>
class StringBase
{
	friend class Rva0036EF70Owner;
public:
	~StringBase() { releaseBuffer(); }
	Char *m_data;
private:
	StringBase();
	StringBase(const StringBase<Char> &src);
	void releaseBuffer();
};

typedef StringBase<char> Rva0036EF70Str;

class Player
{
public:
	char m_pad_00[0x28];
	Rva0036EF70Str m_bfme28;
};

class Object
{
public:
	Player *getControllingPlayer() const;
};

// edi's own layout is unproven past the one field this body reaches.
class Rva0036EF70Sub
{
public:
	char m_pad_00[0x6c];
	_STL::map<int, Rva0036EF70Str> m_bfme6c;
};

class Rva0036EF70Owner
{
public:
	NameKeyType d_0036ef70Method(void);

private:
	void *m_bfme00;			// unproven; +0x4/+0x8 offsets require this slot to exist
	Rva0036EF70Sub *m_04;
	Object *m_08;
};

// ?d_0036ef70@@YAXXZ
NameKeyType Rva0036EF70Owner::d_0036ef70Method(void)
{
	Rva0036EF70Sub *sub = m_04;
	int key = (int)g_theNameKeyGenerator->nameToKey("kq");

	Object *obj = m_08;
	if (obj)
	{
		Player *player = obj->getControllingPlayer();
		if (player)
		{
			Rva0036EF70Str name(player->m_bfme28);
			const char *p = name.m_data ? (const char *)name.m_data + 8 : &g_NAMEKEY_empty_string;
			key = (int)g_theNameKeyGenerator->nameToKey(p);

			_STL::map<int, Rva0036EF70Str>::iterator it = sub->m_bfme6c.find(key);
			if (it != sub->m_bfme6c.end())
			{
				Rva0036EF70Str hit(it->second);
				key = (int)NAMEKEY(*reinterpret_cast<const AsciiString *>(&hit));
			}
		}
	}

	return (NameKeyType)key;
}
