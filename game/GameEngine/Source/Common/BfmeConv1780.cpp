class BfmeTargetGK
{
public:
	virtual void bfmeV0GK(void);
	virtual void bfmeV1GK(void);
	virtual void bfmeV2GK(void);
	virtual void bfmeV3GK(void);
	virtual void bfmeV4GK(void);
	virtual void bfmeV5GK(void);
	virtual void bfmeV6GK(void);
	virtual void bfmeV7GK(void);
	virtual void bfmeV8GK(void);
	virtual void bfmeV9GK(void);
	virtual void bfmeV10GK(void);
	virtual void bfmeV11GK(void);
	virtual void bfmeV12GK(void);
	virtual void bfmeV13GK(void);
	virtual void bfmeV14GK(void);
	virtual void bfmeV15GK(void);
	virtual void bfmeV16GK(void);
	virtual void bfmeV17GK(void);
	virtual void bfmeV18GK(void);
	virtual void bfmeV19GK(void);
	virtual void bfmeV20GK(void);
	virtual void bfmeV21GK(void);
	virtual void bfmeV22GK(void);
	virtual void bfmeV23GK(void);
	virtual void bfmeV24GK(void);
	virtual void bfmeV25GK(void);
	virtual void bfmeV26GK(void);
	virtual void bfmeV27GK(void);
	virtual void bfmeV28GK(void);
	virtual void bfmeV29GK(void);
	virtual void bfmeV30GK(void);
	virtual void bfmeV31GK(void);
	virtual void bfmeV32GK(void);
	virtual void bfmeV33GK(void);
	virtual void bfmeV34GK(void);
	virtual void bfmeV35GK(void);
	virtual void bfmeV36GK(void);
	virtual void bfmeV37GK(void);
	virtual void bfmeV38GK(void);
	virtual void bfmeV39GK(void);
	virtual void bfmeV40GK(void);
	virtual void bfmeV41GK(void);
	virtual void bfmeV42GK(void);
	virtual void bfmeV43GK(void);
	virtual void bfmeV44GK(void);
	virtual void bfmeV45GK(void);
	virtual void bfmeWakeGK(void);
};

class BfmeSourceGK
{
public:
	virtual void bfmeV0GK(void);
	virtual void bfmeV1GK(void);
	virtual void bfmeV2GK(void);
	virtual void bfmeV3GK(void);
	virtual void bfmeV4GK(void);
	virtual void bfmeV5GK(void);
	virtual void bfmeV6GK(void);
	virtual void bfmeV7GK(void);
	virtual void bfmeV8GK(void);
	virtual void bfmeV9GK(void);
	virtual void bfmeV10GK(void);
	virtual void bfmeV11GK(void);
	virtual void bfmeV12GK(void);
	virtual void bfmeV13GK(void);
	virtual void bfmeV14GK(void);
	virtual void bfmeV15GK(void);
	virtual void bfmeV16GK(void);
	virtual void bfmeV17GK(void);
	virtual void bfmeV18GK(void);
	virtual void bfmeV19GK(void);
	virtual void bfmeV20GK(void);
	virtual void bfmeV21GK(void);
	virtual void bfmeV22GK(void);
	virtual void bfmeV23GK(void);
	virtual void bfmeV24GK(void);
	virtual void bfmeV25GK(void);
	virtual BfmeTargetGK *bfmePickGK(void);
};

class BfmeItemGK
{
public:
	unsigned char m_bfmeHeadGK[0x1fc];
	BfmeSourceGK *m_bfmeSourceGK;
};

class BfmeLinkGK
{
public:
	BfmeLinkGK *m_bfmeNextGK;
	int m_bfmeSpareGK;
	BfmeItemGK *m_bfmeItemGK;
};

class BfmeAgentGK
{
public:
	void bfmeNoteGK(BfmeItemGK *item);
};

class AI
{
public:
	unsigned char m_bfmeHeadGK[0xc];
	BfmeAgentGK *m_bfmeAgentGK;
};

extern AI *TheAI;

class BfmeOwnerGK
{
public:
	void bfmeRunGK(void);

	int m_bfmeSpareGK;
	BfmeLinkGK *m_bfmeListGK;
};

void BfmeOwnerGK::bfmeRunGK(void)
{
	for (BfmeLinkGK *link = m_bfmeListGK->m_bfmeNextGK; link != m_bfmeListGK; link = link->m_bfmeNextGK)
	{
		BfmeItemGK *item = link->m_bfmeItemGK;

		TheAI->m_bfmeAgentGK->bfmeNoteGK(item);

		BfmeSourceGK *source = item->m_bfmeSourceGK;

		if (source)
		{
			BfmeTargetGK *target = source->bfmePickGK();

			if (target)
				target->bfmeWakeGK();
		}
	}
}
