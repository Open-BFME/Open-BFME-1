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

class NameKeyGenerator
{
public:
	int bfmeKeyDJ(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class BfmeThingDJ
{
public:
	BfmeItemDJ *bfmeFindDJ(int key);
};

int __cdecl bfmeCheckDJ(BfmeThingDJ *thing)
{
	static int key = TheNameKeyGenerator->bfmeKeyDJ("CastleMemberBehavior");

	BfmeItemDJ *it = thing->bfmeFindDJ(key);

	if (it != 0 && it->m_bfmeFlagDJ != 0 && it->m_bfmeOwnerDJ->m_bfmeAllowDJ != 0)
		return 0;

	return 1;
}
