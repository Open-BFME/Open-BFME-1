// Four call-free bodies that do nothing but write constants -- or copy one
// field onto another -- with no base, no vptr and no branch.
//
// WHAT THE BYTES SHOW, ROW BY ROW.
//
// 0x00082A80 opens `mov eax,3F800000h` and stores eax into six consecutive
// dwords.  There is no `mov eax,ecx`, so it returns nothing and is a void
// member, not a constructor; 3F800000h repeated six times is 1.0f hoisted into
// a register, which is what MSVC 7.1 does once a large immediate recurs.
//
// A FIFTH SIBLING, 0x000C8200, IS THE SAME IDEA AS A CONSTRUCTOR OVER FOUR
// FLOATS AND IS NOT CLAIMED HERE.  It is two bytes longer than anything this
// compiler will emit for it: after `mov eax,ecx` and `mov ecx,3F800000h` retail
// copies `this` a second time into edx and stores through edx, where MSVC 7.1
// stores through eax directly.  A member-initialiser list, body assignments, an
// unrolled loop, a pointer local, an inlined base or member constructor, and
// /O1, /Og, /Oy- and /Ob0 all produce the 19-byte eax form.  What forces the
// extra copy is not known.
//
// 0x005A7A60 is a constructor whose repeated constant is 80000000h; 7FFFFFFFh
// appears once and stays an immediate.  The +4 store is a byte, the rest dwords.
//
// 0x001073F0 is a void member over four dwords and a byte high in the object
// (0x1454..0x1464), with FFFF0001h used twice and 0000FFFFh used twice, each
// hoisted in turn into eax.
//
// 0x00842650 copies three dwords from +0x64, +0x68 and +0x6C onto +4, +8 and
// +0xC and then clears a byte at +0x3A.  The loads interleave with the stores
// (+0x64, +0x68, store +4, +0x6C, store +8, store +0xC), which is a scheduler
// artefact of three SEPARATE member-to-member assignments -- copying a
// three-dword block as one sub-object would have produced a single base
// register and [reg]/[reg+4]/[reg+8].
//
// IDENTITY IS NOT RECOVERED.  Names are address-derived.  3F800000h is read as
// `float` only because 1.0f is the overwhelmingly likelier source spelling than
// the integer 1065353216; the remaining constants are written as the ints they
// encode.

class Rva00082A80
{
public:
	void reset();
	float m_a, m_b, m_c, m_d, m_e, m_f;
};

// @?reset@Rva00082A80@@QAEXXZ 0x00082A80
void Rva00082A80::reset()
{
	m_a = 1.0f;
	m_b = 1.0f;
	m_c = 1.0f;
	m_d = 1.0f;
	m_e = 1.0f;
	m_f = 1.0f;
}

class Rva005A7A60
{
public:
	Rva005A7A60();
	int m_00;
	bool m_04;
	int m_08;
	int m_0C;
	int m_10;
};

// @??0Rva005A7A60@@QAE@XZ 0x005A7A60
Rva005A7A60::Rva005A7A60()
{
	m_00 = 0;
	m_04 = false;
	m_08 = (int)0x80000000;
	m_0C = 0x7FFFFFFF;
	m_10 = (int)0x80000000;
}

class Rva001073F0
{
public:
	void reset();
	char m_lead[ 0x1454 ];
	int m_a;
	int m_b;
	int m_c;
	int m_d;
	bool m_e;
};

// @?reset@Rva001073F0@@QAEXXZ 0x001073F0
void Rva001073F0::reset()
{
	m_a = (int)0xFFFF0001;
	m_b = (int)0xFFFF0001;
	m_c = 0xFFFF;
	m_d = 0xFFFF;
	m_e = false;
}

class Rva00842650
{
public:
	void adopt();
	char m_head[ 4 ];
	int m_a;
	int m_b;
	int m_c;
	char m_gap[ 0x3A - 0x10 ];
	bool m_flag;
	char m_gap2[ 0x64 - 0x3B ];
	int m_srcA;
	int m_srcB;
	int m_srcC;
};

// @?adopt@Rva00842650@@QAEXXZ 0x00842650
void Rva00842650::adopt()
{
	m_a = m_srcA;
	m_b = m_srcB;
	m_c = m_srcC;
	m_flag = false;
}
