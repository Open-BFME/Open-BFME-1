class BfmeTargetZW
{
public:
	virtual void bfmeT0ZW();
	virtual void bfmeT1ZW();
	virtual void bfmeT2ZW();
	virtual void bfmeT3ZW();
	virtual void bfmeT4ZW();
	virtual void bfmeSetZW(void *arg);
};

class BfmeSubZW
{
public:
	virtual void bfmeS00ZW();
	virtual void bfmeS01ZW();
	virtual void bfmeS02ZW();
	virtual void bfmeS03ZW();
	virtual void bfmeS04ZW();
	virtual void bfmeS05ZW();
	virtual void bfmeS06ZW();
	virtual void bfmeS07ZW();
	virtual void bfmeS08ZW();
	virtual void bfmeS09ZW();
	virtual void bfmeS10ZW();
	virtual void bfmeS11ZW();
	virtual void bfmeS12ZW();
	virtual void bfmeS13ZW();
	virtual void bfmeS14ZW();
	virtual void bfmeS15ZW();
	virtual void bfmeS16ZW();
	virtual BfmeTargetZW *bfmeGetZW();
};

class BfmeItemZW
{
public:
	unsigned char m_bfmeHeadZW[0xc];
	BfmeSubZW m_bfmeSubZW;
};

class BfmeThingZW
{
public:
	char bfmeHasZW(int what);

	unsigned char m_bfmeHeadZW[0x1f0];
	BfmeItemZW **m_bfmeListZW;
};

class BfmeOuterZW
{
public:
	void *m_bfmeArgZW;
};

class BfmeOwnerZW
{
public:
	void bfmeApplyZW(BfmeThingZW *thing, void *b, void *c);

	unsigned char m_bfmeHeadZW[4];
	char m_bfmeFlagZW;
};

void BfmeOwnerZW::bfmeApplyZW(BfmeThingZW *thing, void *b, void *c)
{
	if (m_bfmeFlagZW == 0)
		return;

	if (thing == 0)
		return;

	if (thing->bfmeHasZW(0x65) == 0)
		return;

	for (BfmeItemZW **p = thing->m_bfmeListZW; *p != 0; p++)
	{
		BfmeTargetZW *t = (*p)->m_bfmeSubZW.bfmeGetZW();

		if (t != 0)
			t->bfmeSetZW(((BfmeOuterZW *)((char *)this - 0x30))->m_bfmeArgZW);
	}
}
