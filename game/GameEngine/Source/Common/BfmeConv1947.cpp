class BfmeKeyGenEQW
{
public:
	int bfmeNameToKeyEQW(const char *name);
};

extern BfmeKeyGenEQW *g_bfmeKeyGenEQW;

class BfmeModuleEQW
{
public:
	void bfmeDoEQW();
};

class BfmeThingEQW
{
public:
	BfmeModuleEQW *bfmeFindEQW(int key);
};

class BfmeSubEQW
{
public:
	char bfmeCheckEQW();
	void bfmeApplyEQW(BfmeThingEQW *thing, int mode);
};

class BfmeOwnerEQW
{
public:
	unsigned char m_bfmeHeadEQW[0x78];
	BfmeSubEQW *m_bfmeSubEQW;
	unsigned char m_bfmeMidEQW[4];
	unsigned char m_bfmeFlagsEQW;
};

class BfmeHostEQW
{
public:
	void bfmeGoEQW(BfmeThingEQW *thing);

	unsigned char m_bfmeHeadEQW[4];
	BfmeOwnerEQW *m_bfmeOwnerEQW;
};

void BfmeHostEQW::bfmeGoEQW(BfmeThingEQW *thing)
{
	BfmeOwnerEQW *owner = m_bfmeOwnerEQW;
	BfmeSubEQW *sub = owner->m_bfmeSubEQW;

	if (sub != 0 && !sub->bfmeCheckEQW())
		sub->bfmeApplyEQW(thing, 0);

	if ((owner->m_bfmeFlagsEQW & 0x40) != 0)
	{
		static int s_bfmeKeyEQW =
			g_bfmeKeyGenEQW->bfmeNameToKeyEQW("DetachableRiderUpdate");

		BfmeModuleEQW *mod = thing->bfmeFindEQW(s_bfmeKeyEQW);

		if (mod != 0)
			mod->bfmeDoEQW();
	}
}
