class BfmeThingMD;

class BfmeInnerMD
{
public:
	BfmeThingMD *bfmeResolveMD(void);
};

class BfmeThingMD
{
public:
	int m_bfmeSpareMD;
	BfmeInnerMD *m_bfmeInnerMD;
	unsigned char m_bfmeGapMD[0xcc];
	int m_bfmeFlagsMD;
};

class BfmeSubMD
{
public:
	char bfmeTestMD(void);
};

class BfmeItemMD
{
public:
	int m_bfmeSpareMD;
	BfmeSubMD *m_bfmeSubMD;
};

class BfmeHolderMD
{
public:
	BfmeItemMD *bfmeFindMD(int flag);

	int m_bfmeSpareMD;
	BfmeThingMD *m_bfmeThingMD;
};

class BfmeOwnerMD
{
public:
	char bfmeCheckMD(void);

	unsigned char m_bfmeHeadMD[8];
	BfmeHolderMD *m_bfmeHolderMD;
};

char BfmeOwnerMD::bfmeCheckMD(void)
{
	BfmeHolderMD *holder = m_bfmeHolderMD;
	BfmeThingMD *thing = holder->m_bfmeThingMD;

	if (thing && thing->m_bfmeInnerMD)
		thing = thing->m_bfmeInnerMD->bfmeResolveMD();

	if (thing->m_bfmeFlagsMD & 0x400000)
	{
		BfmeItemMD *item = holder->bfmeFindMD(0);

		if (item)
			return item->m_bfmeSubMD->bfmeTestMD();

		return 1;
	}

	return 0;
}
