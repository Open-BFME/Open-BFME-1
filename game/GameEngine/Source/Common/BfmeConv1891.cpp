struct BfmeMarkAC
{
	unsigned char m_bfmeOneAC;
	unsigned char m_bfmeTwoAC;
};

class BfmeItemAC
{
public:
	virtual void bfmeV0AC();
	virtual void bfmeV1AC();
	virtual void bfmeV2AC();
	virtual void bfmeV3AC();
	virtual char bfmeDoneAC();
	virtual void bfmeV5AC();
	virtual void bfmeV6AC();
	virtual void bfmeV7AC();
	virtual void bfmeV8AC();
	virtual void bfmeV9AC();
	virtual void bfmeMarkAC(BfmeMarkAC *mark);
};

void __cdecl bfmeVisitAC(BfmeItemAC *item, void *slot);

class BfmeOwnerAC
{
public:
	void bfmeDoAC(BfmeItemAC *item);

	void bfmeAddAC(BfmeItemAC *item);

	unsigned char m_bfmeHeadAC[0xcc];
	void *m_bfmeSlotsAC[10];
};

void BfmeOwnerAC::bfmeDoAC(BfmeItemAC *item)
{
	BfmeMarkAC mark;
	unsigned char set = 1;

	mark.m_bfmeOneAC = set;
	mark.m_bfmeTwoAC = set;

	item->bfmeMarkAC(&mark);

	bfmeAddAC(item);

	if (item->bfmeDoneAC() != 0)
		return;

	for (int i = 0; i < 10; i++)
		bfmeVisitAC(item, &m_bfmeSlotsAC[i]);
}
