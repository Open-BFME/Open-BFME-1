// cl: /DNDEBUG /DWIN32 /MD /EHsc
//
// Address-derived owner for retail 0x005927F0 (240 bytes).  The two one-word
// fields at +0x08 and +0x0c are embedded Rva00590790 holders: the retail EH
// map calls that holder destructor on this+8 and this+0xc, while the normal
// path inlines its held-pointer delete.  The held type is UpgradeMuxData,
// named by its destructor: ILT RVA 0x0003FA7B jumps to the matched ??1UpgradeMuxData@@QAE@XZ (0x0098C4C0).

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

extern void j_000347d9();
class UpgradeMuxData
{
public:
	~UpgradeMuxData();
};

class Rva00590790
{
public:
	__forceinline ~Rva00590790()
	{
		UpgradeMuxData *held = m_held;
		if (held != 0)
		{
			delete held;
		}
	}

	UpgradeMuxData *m_held;
};

// The 0x012F12CC singleton is DisplayStringManager *TheDisplayStringManager,
// defined once in DisplayStringManager.cpp.  This TU keeps its own view of
// the vtable and casts at the use.
class DisplayStringManager;

class Rva0048EC80Manager
{
public:
	virtual void _s00();
	virtual void _s01();
	virtual void _s02();
	virtual void _s03();
	virtual void _s04();
	virtual void _s05();
	virtual void _s06();
	virtual void _s07();
	virtual void _s08();
	virtual void _s09();
	virtual void release(int handle);
};

extern DisplayStringManager *TheDisplayStringManager;
static inline Rva0048EC80Manager *theDisplayStringManagerView()
{
	return (Rva0048EC80Manager *)TheDisplayStringManager;
}

// The held-string table at VA 0x012F19E8 is recorded as
// ?g_s4Holder@@3PAUS4Holder0046DBB0@@A in
// targets/game/reverse/dir32_addresses.csv, and S4DrainStringVector.cpp views
// the same object as a struct.  Declared as a struct here so this TU's extern
// mangles to that recorded name directly, with no linker alias.
struct S4Holder0046DBB0
{
};

extern S4Holder0046DBB0 *g_s4Holder;

typedef void (S4Holder0046DBB0::*S4HolderStringMember)(
	const AsciiString *);

union S4HolderStringCast
{
	void (*raw)();
	S4HolderStringMember member;
};

static __forceinline void callS4HolderString(
	S4Holder0046DBB0 *holder, void (*function)(), AsciiString *text)
{
	S4HolderStringCast cast;
	cast.raw = function;
	(holder->*cast.member)(text);
}

class Rva00592640Owner
{
public:
	~Rva00592640Owner();

private:
	unsigned char m_unreconstructed_00[4];
	int m_unreconstructed_04;
	Rva00590790 m_member8;
	Rva00590790 m_memberC;
	unsigned char m_unreconstructed_10[4];
	int m_drop1;
	int m_drop2;
	int m_drop3;
	int m_drop4;
	int m_drop5;
};

// ??1Rva00592640Owner@@QAE@XZ
Rva00592640Owner::~Rva00592640Owner()
{
	theDisplayStringManagerView()->release(m_drop1);
	theDisplayStringManagerView()->release(m_drop2);
	theDisplayStringManagerView()->release(m_drop3);
	theDisplayStringManagerView()->release(m_drop4);
	theDisplayStringManagerView()->release(m_drop5);

	{
		AsciiString text("HelpBoxText");
		callS4HolderString(
			g_s4Holder,
			j_000347d9, &text);
	}
}
