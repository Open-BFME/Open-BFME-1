// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Retail 0x00591640 (322 bytes): destructor of the Rva00597FC0Client member at
// +0x68.  Rva00597FC0Client's destructor (GameClientDestructor.cpp, 0x00596500)
// calls it through ILT 0x0003760A, and an unwind funclet uses the same ILT as
// a destructor.  It removes the six Palantir/<layout>/ Apt objects and their
// Timer twins, then the inline base destructor clears the active flag.
//
// SHAPE.  Retail spills `this` and runs the loop under EH state 0, dropping to
// -1 just before the active-flag test: the flag handling is an inlined base
// (or leading member) destructor, not the body's tail.  The '/' separator is a
// two-byte buffer at the bottom of its stack dword, as AsciiString::concat(char)
// would build it.

#include <hash_map>

#include "../../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

// Retail expands concat(char) here: the character goes into a two-byte buffer
// at the bottom of its stack dword and the length-1 concat is called.
template <>
inline void StringBase<char>::concat(char c)
{
	char text[2];
	text[0] = c;
	concat(text, 1);
}

struct Rva0046AF20Mapped
{
	void *m_callback;
};

namespace rts
{
	template <class T> struct hash;
	template <class T> struct equal_to;

	template <> struct hash<AsciiString>
	{
		unsigned int operator()(AsciiString value) const;
	};

	template <> struct equal_to<AsciiString>
	{
		int operator()(const AsciiString &left, const AsciiString &right) const;
	};
}

typedef std::hash_map<AsciiString, Rva0046AF20Mapped,
	rts::hash<AsciiString>, rts::equal_to<AsciiString> > Rva0046AF20Map;

class WindowManager
{
public:
	void removeAptObject(const AsciiString &name);

private:
	unsigned char m_padding[0x94];
	Rva0046AF20Map m_callbacks;
};

// Retail 0x012F19E8 is ?g_rva012F19E8WindowManager@@3PAVWindowManager@@A
// (data_rows.csv, GUI/WindowManager.cpp); g_theWindowManager was only a pin.
extern WindowManager *g_rva012F19E8WindowManager;
#define g_theWindowManager g_rva012F19E8WindowManager
extern void j_00001f32();
extern void j_0003d54b();

class BfmeLayoutVHH
{
};

extern void bfmeGoVHH(char index, BfmeLayoutVHH *name);
AsciiString operator+(AsciiString left, const AsciiString &right);

typedef void (WindowManager::*WindowManagerStringMember)(const AsciiString *);

union WindowManagerStringCast
{
	void (*raw)();
	WindowManagerStringMember member;
};

static __forceinline void callWindowManagerString(
	WindowManager *manager, void (*function)(), AsciiString *name)
{
	WindowManagerStringCast cast;
	cast.raw = function;
	(manager->*cast.member)(name);
}

class Rva00591640ActiveBase
{
public:
	~Rva00591640ActiveBase()
	{
		if (m_active)
		{
			j_00001f32();
			m_active = false;
		}
	}

protected:
	unsigned char m_padding[8];
	bool m_active;
};

class Rva00597FC0ClientMember68 : public Rva00591640ActiveBase
{
public:
	~Rva00597FC0ClientMember68();
};

Rva00597FC0ClientMember68::~Rva00597FC0ClientMember68()
{
	int index;

	if (g_theWindowManager != 0)
	{
		{
			AsciiString name("Palantir/CommandUI/PortraitBackground");
			g_theWindowManager->removeAptObject(name);
		}

		for (index = 0; index < 6; ++index)
		{
			AsciiString name;
			bfmeGoVHH((char)index, (BfmeLayoutVHH *)&name);
			name.concat('/');
			g_theWindowManager->removeAptObject(
				AsciiString("Palantir/") + name);
			name.StringBase<char>::concat("Timer", 5);
			callWindowManagerString(g_theWindowManager, j_0003d54b, &name);
		}
	}
}
