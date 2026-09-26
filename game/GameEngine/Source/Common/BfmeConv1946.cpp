class BfmeSubEQT
{
public:
	char bfmeAEQT();
	char bfmeBEQT();
};

class BfmeHoldEQT
{
public:
	unsigned char m_bfmeHeadEQT[4];
	BfmeSubEQT *m_bfmeSubEQT;
};

class BfmeThingEQT
{
public:
	char bfmeCEQT(int what);
};

class BfmeBaseEQT
{
public:
	BfmeBaseEQT() { m_bfmeZeroEQT = 0; }

	int m_bfmeZeroEQT;
};

class BfmeObjEQT : public BfmeBaseEQT
{
public:
	BfmeObjEQT(BfmeThingEQT *owner) { m_bfmeOwnerEQT = owner; }
	virtual ~BfmeObjEQT() {}

	char bfmeRunEQT(void *arg);

	BfmeThingEQT *m_bfmeOwnerEQT;
};

char bfmeCheckEQT(BfmeThingEQT *thing, void *arg, BfmeHoldEQT *hold)
{
	if (hold != 0 && arg != 0 &&
		!hold->m_bfmeSubEQT->bfmeAEQT() &&
		!hold->m_bfmeSubEQT->bfmeBEQT() &&
		thing->bfmeCEQT(0x3a))
	{
		BfmeObjEQT obj(thing);

		if (!obj.bfmeRunEQT(arg))
			return 0;
	}

	return 1;
}
