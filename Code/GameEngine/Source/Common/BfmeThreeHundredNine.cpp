class ModelConditionFlags
{
public:
	unsigned int m_bfmeFlags;
	unsigned char m_bfmeTail[0x24];
};

struct BfmeRecordOwnerRB
{
	unsigned char m_bfmeHead[0x110];
	ModelConditionFlags m_bfmeRecord;
};

class Drawable
{
public:
	void replaceModelConditionState(const ModelConditionFlags &state, bool dirty, unsigned int effect);
};

class BfmeNodeRB
{
public:
	__declspec(noinline) void bfmeTellRB(void *what);
	unsigned char m_bfmeHead[0xfc];
	BfmeRecordOwnerRB *m_bfmeRecordOwner;
	unsigned int m_bfmeSpare;
	BfmeNodeRB *m_bfmeNext;
};

void BfmeNodeRB::bfmeTellRB(void *what)
{
	BfmeRecordOwnerRB *owner = m_bfmeRecordOwner;
	ModelConditionFlags record = owner->m_bfmeRecord;

	if ((unsigned int)what == 4)
		record.m_bfmeFlags |= 0x80;
	else
		record.m_bfmeFlags &= ~0x80;

	((Drawable *)this)->replaceModelConditionState(record, false, 0);
}

class BfmeHolderRB
{
public:
	virtual void bfmeSpareRB0();
	virtual void bfmeSpareRB1();
	virtual void bfmeSpareRB2();
	virtual void bfmeSpareRB3();
	virtual void bfmeSpareRB4();
	virtual void bfmeSpareRB5();
	virtual void bfmeSpareRB6();
	virtual void bfmeSpareRB7();
	virtual void bfmeSpareRB8();
	virtual void bfmeSpareRB9();
	virtual void bfmeSpareRBA();
	virtual void bfmeSpareRBB();
	virtual BfmeNodeRB *bfmeHeadRB();
	void bfmeTellAllRB(void *what);
};

void BfmeHolderRB::bfmeTellAllRB(void *what)
{
	for (BfmeNodeRB *at = bfmeHeadRB(); at != 0; at = at->m_bfmeNext)
		at->bfmeTellRB(what);
}
