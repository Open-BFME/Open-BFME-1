// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// stlport
// Two masked table reads, an assignment returning the receiver, and a four-state test.

#include "Common/BitFlags.h"

// Retail VA 0x012A9200: eleven string addresses followed by a null cell.
// Preserve the existing PE32/MSVC int[] address-storage interface used by
// both callers; this is not a claim about the original C++ element type.
// Each cast below emits a static DIR32 relocation, not initializer code.
// See identity_evidence/0x00ea9200-disabled-name-cells.md.
extern const char g_Va01081720[] = "DEFAULT";
extern const char g_Va01086434[] = "DISABLED_UNUSED";
extern const char g_Va01086424[] = "DISABLED_EMP";
extern const char g_Va01086414[] = "DISABLED_HELD";
extern const char g_Va010863FC[] = "DISABLED_PARALYZED";
extern const char g_Va010863E4[] = "DISABLED_UNMANNED";
extern const char g_Va010863C8[] = "DISABLED_UNDERPOWERED";
extern const char g_Va010863B0[] = "DISABLED_FREEFALL";
extern const char g_Va01086390[] = "DISABLED_TEMPORARILY_BUSY";
extern const char g_Va01086370[] = "DISABLED_SCRIPT_DISABLED";
extern const char g_Va0108634C[] = "DISABLED_SCRIPT_UNDERPOWERED";

int g_bfmeTableDJa[12] =
{
	reinterpret_cast<int>(g_Va01081720),
	reinterpret_cast<int>(g_Va01086434),
	reinterpret_cast<int>(g_Va01086424),
	reinterpret_cast<int>(g_Va01086414),
	reinterpret_cast<int>(g_Va010863FC),
	reinterpret_cast<int>(g_Va010863E4),
	reinterpret_cast<int>(g_Va010863C8),
	reinterpret_cast<int>(g_Va010863B0),
	reinterpret_cast<int>(g_Va01086390),
	reinterpret_cast<int>(g_Va01086370),
	reinterpret_cast<int>(g_Va0108634C),
	0
};

class Gen_001C3F80
{
public:
	int bfmeLookup(int index) const;

private:
	unsigned int m_bfmeMask;				// +0x00
};

// ?bfmeLookup@Gen_001C3F80@@QBEHH@Z
int Gen_001C3F80::bfmeLookup(int index) const
{
	if (m_bfmeMask & (1 << (index & 31)))
		return g_bfmeTableDJa[index];

	return 0;
}

class Gen_0020EC30
{
public:
	int bfmeLookup(int index) const;

private:
	unsigned int m_bfmeMask;				// +0x00
};

// ?bfmeLookup@Gen_0020EC30@@QBEHH@Z
int Gen_0020EC30::bfmeLookup(int index) const
{
	if (m_bfmeMask & (1 << (index & 31)))
		return (int)BitFlags<11>::getBitNames()[index];

	return 0;
}

class BfmeTripleDJ
{
public:
	int m_bfmeFirst;					// +0x00
	int m_bfmeSecond;					// +0x04
	int m_bfmeThird;					// +0x08
};

class Gen_00233CC0
{
public:
	Gen_00233CC0 &bfmeAssign(const Gen_00233CC0 &other);

private:
	BfmeTripleDJ m_bfmeTriple;				// +0x00
	int m_bfmeExtra;					// +0x0C
};

// ?bfmeAssign@Gen_00233CC0@@QAEAAV1@ABV1@@Z
Gen_00233CC0 &Gen_00233CC0::bfmeAssign(const Gen_00233CC0 &other)
{
	m_bfmeTriple = other.m_bfmeTriple;

	m_bfmeExtra = other.m_bfmeExtra;

	return *this;
}

class Gen_001F83C0
{
public:
	int bfmeActive(void) const;

private:
	int m_bfmeHead[18];					// +0x00
	bool m_bfmeArmed;					// +0x48
	char m_bfmeGap[0x17];					// +0x49
	int m_bfmeState;					// +0x60
};

// ?bfmeActive@Gen_001F83C0@@QBEHXZ
int Gen_001F83C0::bfmeActive(void) const
{
	if (m_bfmeArmed && (m_bfmeState == 1 || m_bfmeState == 2 || m_bfmeState == 3 || m_bfmeState == 4))
		return 1;

	return 0;
}
