// Six __thiscall constructors that write nothing but constants into their own
// members, with no base and no call:
//
//     mov eax,ecx / xor ecx,ecx / <stores through eax> / ret
//
// WHAT THE BYTES SHOW.  `mov eax,ecx` at the head returns `this`, so these are
// constructors.  ecx is zeroed once and reused for every zero store, which is
// how MSVC 7.1 spells a run of zero initialisers; a non-zero constant that
// appears once stays an immediate.  Store WIDTH is member type: `mov dword ptr`
// is a four-byte member, `mov byte ptr` a one-byte one, so the bool members are
// readable straight off the encoding.
//
// STORE ORDER IS SOURCE ORDER, AND ONE ROW PROVES IT.  0x0043BBC0 writes +0x1C
// (3F800000h, i.e. 1.0f) BEFORE +0x10, then +0x20 last; a member-initialiser
// list would have been reordered into declaration order, so that constructor's
// body assigns its members in the order written here.  Where the order is
// already ascending the bytes cannot tell a body from an initialiser list, and
// the body form is used throughout for consistency.
//
// ONE ROW HAS A VPTR: 0x001B7450 opens `mov dword ptr [eax],<VFTABLE>` before
// any member store, which is where MSVC always puts it.  The other five open
// with a plain zero store at +0, so their offset 0 is a member.
//
// IDENTITY IS NOT RECOVERED.  Names are address-derived.  A dword zero cannot
// distinguish int from pointer from float, so every zeroed dword is `int`
// except where a 3F800000h store in the same object makes `float` the reading.

class Rva001B7450
{
public:
	Rva001B7450();
	virtual void keep();
	int m_a;
	int m_b;
	int m_c;
	int m_d;
	bool m_e;
	int m_f;
	int m_g;
	int m_h;
};

// @??0Rva001B7450@@QAE@XZ 0x001B7450
Rva001B7450::Rva001B7450()
{
	m_a = 0;
	m_b = 0;
	m_c = 0;
	m_d = 0;
	m_e = false;
	m_f = 0;
	m_g = 0;
	m_h = 0;
}

class Rva0043BBC0
{
public:
	Rva0043BBC0();
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	float m_10;
	int m_14;
	int m_18;
	float m_1C;
	int m_20;
};

// @??0Rva0043BBC0@@QAE@XZ 0x0043BBC0
Rva0043BBC0::Rva0043BBC0()
{
	m_00 = 0;
	m_04 = 0;
	m_08 = 0;
	m_0C = 0;
	m_14 = 0;
	m_18 = 0;
	m_1C = 1.0f;
	m_10 = 0.0f;
	m_20 = 0x20;
}

class Rva005886E0
{
public:
	Rva005886E0();
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	float m_10;
	int m_14;
	int m_18;
	bool m_1C;
	bool m_1D;
};

// @??0Rva005886E0@@QAE@XZ 0x005886E0
Rva005886E0::Rva005886E0()
{
	m_00 = 0;
	m_04 = 0;
	m_08 = 0;
	m_0C = 0;
	m_10 = 1.0f;
	m_14 = 0;
	m_18 = 0;
	m_1C = false;
	m_1D = false;
}

class Rva0060AA40
{
public:
	Rva0060AA40();
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	float m_10;
	bool m_14;
	bool m_15;
	bool m_16;
	int m_18;
};

// @??0Rva0060AA40@@QAE@XZ 0x0060AA40
Rva0060AA40::Rva0060AA40()
{
	m_00 = 0;
	m_04 = 0;
	m_08 = 0;
	m_0C = 0;
	m_10 = 1.0f;
	m_14 = false;
	m_15 = false;
	m_16 = false;
	m_18 = 0;
}

class Rva00762070
{
public:
	Rva00762070();
	int m_00;
	bool m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
	bool m_20;
};

// @??0Rva00762070@@QAE@XZ 0x00762070
Rva00762070::Rva00762070()
{
	m_00 = 0;
	m_04 = false;
	m_08 = 0;
	m_0C = 0;
	m_10 = 0;
	m_14 = 0;
	m_18 = 0;
	m_1C = 0;
	m_20 = false;
}
