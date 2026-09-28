struct Rva00579160Manager
{
	virtual void bfmeSlot0EV();
	virtual void bfmeSlot1EV();
	virtual void bfmeSlot2EV();
	virtual void bfmeSlot3EV();
	virtual void bfmeSlot4EV();
	virtual void bfmeSlot5EV();
	virtual void bfmeSlot6EV();
	virtual void bfmeSlot7EV();
	virtual void bfmeSlot8EV();
	virtual void bfmeSlot9EV();
	virtual const float *bfmeScaleEV();
};

extern Rva00579160Manager *Rva00579160TheManager;

class BfmeCellEV
{
public:
	unsigned char m_bfmeHeadEV[0x24];
	int m_bfmeWEV;
	int m_bfmeHEV;
};

class BfmeVec2EV
{
public:
	float m_bfmeXEV;
	float m_bfmeYEV;
};

class BfmeHostEV
{
public:
	void bfmeExtentsEV(BfmeVec2EV *a, BfmeVec2EV *b, BfmeVec2EV *out);

	unsigned char m_bfmeHeadEV[0x28];
	BfmeCellEV *m_bfmeFirstEV;
	BfmeCellEV *m_bfmeSecondEV;
};

void BfmeHostEV::bfmeExtentsEV(BfmeVec2EV *a, BfmeVec2EV *b, BfmeVec2EV *out)
{
	const float *k = Rva00579160TheManager->bfmeScaleEV();

	if (m_bfmeFirstEV != 0)
	{
		a->m_bfmeXEV = m_bfmeFirstEV->m_bfmeWEV * k[0];
		a->m_bfmeYEV = m_bfmeFirstEV->m_bfmeHEV * k[1];
	}
	else
	{
		a->m_bfmeXEV = 0.0f;
		a->m_bfmeYEV = 0.0f;
	}

	if (m_bfmeSecondEV != 0)
	{
		b->m_bfmeXEV = m_bfmeSecondEV->m_bfmeWEV * k[0];
		b->m_bfmeYEV = m_bfmeSecondEV->m_bfmeHEV * k[1];
	}
	else
	{
		b->m_bfmeXEV = 0.0f;
		b->m_bfmeYEV = 0.0f;
	}

	out->m_bfmeXEV = a->m_bfmeXEV > b->m_bfmeXEV ? a->m_bfmeXEV : b->m_bfmeXEV;
	out->m_bfmeYEV = a->m_bfmeYEV > b->m_bfmeYEV ? a->m_bfmeYEV : b->m_bfmeYEV;
}
