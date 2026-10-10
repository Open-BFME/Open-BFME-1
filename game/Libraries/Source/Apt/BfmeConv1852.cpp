// Retail calls Gen_008D2C80::bfmePush (0x008D2C80) here; bfmePushXS was a
// stand-in spelling of that body, so declare the defining owner and use it.
class Gen_008D2C80
{
public:
	void bfmePush(void);
};

class AssetManagerImpl
{
public:
	void bfmeApplyXS(void *what, void *sub);
};

class BfmeThingDXH
{
public:
	void bfmeGoDXH(void *a);
};

class BfmeA1210
{
public:
	void bfmePop1210();
};

class BfmeOwnerXS
{
public:
	void bfmeRunXS(AssetManagerImpl *thing, void *what, void *flag);

	int m_bfmeModeXS;
	unsigned char m_bfmePadXS[4];
	unsigned char m_bfmeSubXS[4];
};

void BfmeOwnerXS::bfmeRunXS(AssetManagerImpl *thing, void *what, void *flag)
{
	if (flag != 0)
	{
		((Gen_008D2C80 *)thing)->bfmePush();
		((BfmeThingDXH *)thing)->bfmeGoDXH(flag);
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
		((BfmeA1210 *)thing)->bfmePop1210();
}
