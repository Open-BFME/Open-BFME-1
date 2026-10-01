class BfmeOwnerDJ
{
public:
	unsigned char m_bfmeHeadDJ[0x29];
	unsigned char m_bfmeAllowDJ;
};

class BfmeItemDJ
{
public:
	unsigned char m_bfmeHeadDJ[4];
	BfmeOwnerDJ *m_bfmeOwnerDJ;
	unsigned char m_bfmeMidDJ[0x1d];
	unsigned char m_bfmeFlagDJ;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
// Retail returns the enum by value; MSVC mangles a by-value enum return as
// ?AW4NameKeyType@@, which is the matched defining symbol (0x0008FFC0).
enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	NAMEKEY_MAX = 1 << 23,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class BfmeThingDJ
{
public:
	BfmeItemDJ *bfmeFindDJ(int key);
};

int __cdecl bfmeCheckDJ(BfmeThingDJ *thing)
{
	static NameKeyType key = TheNameKeyGenerator->nameToKey("CastleMemberBehavior");

	BfmeItemDJ *it = thing->bfmeFindDJ(key);

	if (it != 0 && it->m_bfmeFlagDJ != 0 && it->m_bfmeOwnerDJ->m_bfmeAllowDJ != 0)
		return 0;

	return 1;
}
