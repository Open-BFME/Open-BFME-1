class BfmeThingXS
{
public:
	void bfmePushXS();
	void bfmeGoXS(void *flag);
	void bfmeApplyXS(void *what, void *sub);
	void bfmePopXS();
};

class BfmeOwnerXS
{
public:
	void bfmeRunXS(BfmeThingXS *thing, void *what, void *flag);

	int m_bfmeModeXS;
	unsigned char m_bfmePadXS[4];
	unsigned char m_bfmeSubXS[4];
};

void BfmeOwnerXS::bfmeRunXS(BfmeThingXS *thing, void *what, void *flag)
{
	if (flag != 0)
	{
		thing->bfmePushXS();
		thing->bfmeGoXS(flag);
	}

	switch (m_bfmeModeXS)
	{
	case 1:
		thing->bfmeApplyXS(what, m_bfmeSubXS);
		break;
	case 10:
		thing->bfmeApplyXS(what, m_bfmeSubXS);
		break;
	}

	if (flag != 0)
		thing->bfmePopXS();
}
