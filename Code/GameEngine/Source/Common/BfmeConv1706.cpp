class BfmeInnerFX
{
public:
	char bfmeReadyFX(void);

	unsigned char m_bfmeHeadFX[0x68];
	int m_bfmeValueFX;
};

class BfmeThingFX
{
public:
	unsigned char m_bfmeHeadFX[4];
	BfmeInnerFX *m_bfmeInnerFX;
};

class BfmeFinderFX
{
public:
	BfmeThingFX *bfmeFindFX(int *out);
};

class BfmeHolderFX
{
public:
	unsigned char m_bfmeHeadFX[0x10];
	BfmeFinderFX *m_bfmeFinderFX;
};

class BfmeOwnerFX
{
public:
	char bfmeCheckFX(void);

	unsigned char m_bfmeHeadFX[0x1c];
	BfmeHolderFX *m_bfmeHolderFX;
};

char BfmeOwnerFX::bfmeCheckFX(void)
{
	int scratch;
	int *out = &scratch;
	BfmeFinderFX *finder = m_bfmeHolderFX->m_bfmeFinderFX;

	BfmeThingFX *thing = finder->bfmeFindFX(out);
	if (thing != 0)
	{
		if (thing->m_bfmeInnerFX->bfmeReadyFX())
			return 1;

		if (thing->m_bfmeInnerFX->m_bfmeValueFX >= 0)
			return 1;
	}

	return 0;
}
