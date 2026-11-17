// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/zhcanonascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// stlport
class INI
{
public:
	static void parseBool(INI *ini, void *instance, void *store, const void *userData);
	static void parseIndexList(INI *ini, void *instance, void *store, const void *userData);
};

#include "../../Include/Common/FieldParse.h"

class MultiIniFieldParse
{
public:
	void add(const FieldParse *fields, unsigned int extra);
};

extern const FieldParse g_bfmeBaseTableABF[];

// Retail .data VA 0x012AC188 (three entries + zero terminator, 64 B): the
// builder below patches slot 2's user data and offset and re-zeroes slot 3 on
// first call, so the static image holds slot 2 unpatched.
FieldParse g_bfmeTableABF[] =
{
	{ "KillArmorUpgrade", INI::parseBool, 0, 0x70 },
	{ "IgnoreArmorUpgrade", INI::parseBool, 0, 0x71 },
	{ "ArmorSetFlag", INI::parseIndexList, 0, 0x0 },
	{ 0, 0, 0, 0 }
};
#include "Common/BitFlags.h"

unsigned int g_bfmeGuardDwordABF = 0;

void bfmeBuildABF(MultiIniFieldParse *p);

void bfmeBuildABF(MultiIniFieldParse *p)
{
	p->add(g_bfmeBaseTableABF, 8);

	unsigned int mask = 1;
	unsigned int zero = 0;

	if ((g_bfmeGuardDwordABF & mask) == 0)
	{
		g_bfmeGuardDwordABF |= mask;

		g_bfmeTableABF[2].userData = BitFlags<11>::getBitNames();
		g_bfmeTableABF[2].offset = 0x74;
		g_bfmeTableABF[3].token = (const char *)zero;
		g_bfmeTableABF[3].parse = (void (*)(INI *, void *, void *, const void *))zero;
		g_bfmeTableABF[3].userData = (const void *)zero;
		g_bfmeTableABF[3].offset = zero;
	}

	p->add(g_bfmeTableABF, zero);
}
