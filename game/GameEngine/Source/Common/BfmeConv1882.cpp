class BfmeKeyZP
{
public:
	unsigned char m_bfmeHeadZP[4];
	int m_bfmeIdZP;
};

class BfmeSlotZP
{
public:
	void bfmeHitZP(BfmeKeyZP *key);

	unsigned char m_bfmeHeadZP[8];
	int m_bfmeIdZP;
	unsigned char m_bfmeTailZP[0x74];
};

class BfmeOwnerZP
{
public:
	void bfmeFindZP(BfmeKeyZP *key);

	unsigned char m_bfmeHeadZP[0x1c];
	BfmeSlotZP *m_bfmeSlotsZP;
	int m_bfmeCountZP;
};

void BfmeOwnerZP::bfmeFindZP(BfmeKeyZP *key)
{
	BfmeSlotZP *p = m_bfmeSlotsZP;
	BfmeSlotZP *end = m_bfmeSlotsZP + m_bfmeCountZP;
	int want = key->m_bfmeIdZP;

	while (p < end)
	{
		if (p->m_bfmeIdZP == want)
		{
			p->bfmeHitZP(key);
			return;
		}

		p++;
	}
}
