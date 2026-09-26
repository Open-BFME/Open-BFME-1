class BfmeVec3HN
{
public:
	float m_bfmeXHN;
	float m_bfmeYHN;
	float m_bfmeZHN;
};

class GeometryInfo
{
public:
	float getMaxHeightAbovePosition() const;
};

class BfmeObjHN
{
public:
	unsigned char m_bfmeHeadHN[0x38];
	float m_bfme38HN;
	float m_bfme3cHN;
	float m_bfme40HN;
	unsigned char m_bfmeGap2HN[0x68];
	GeometryInfo m_bfmeGeomHN;
};

struct Rva003FD060TerrainLogic
{
	virtual void bfmeVt00HN();
	virtual void bfmeVt01HN();
	virtual void bfmeVt02HN();
	virtual void bfmeVt03HN();
	virtual void bfmeVt04HN();
	virtual void bfmeVt05HN();
	virtual void bfmeVt06HN();
	virtual void bfmeVt07HN();
	virtual void bfmeVt08HN();
	virtual void bfmeVt09HN();
	virtual void bfmeVt10HN();
	virtual void bfmeVt11HN();
	virtual void bfmeVt12HN();
	virtual void bfmeVt13HN();
	virtual void bfmeVt14HN();
	virtual bool bfmeReachHN(BfmeVec3HN *a, BfmeVec3HN *b);
};

class BfmeAiHelperHN
{
public:
	bool bfmeBlockedHN(BfmeObjHN *o, BfmeVec3HN *b);
};

class AI
{
public:
	unsigned char m_bfmeHeadHN[0xc];
	BfmeAiHelperHN *m_bfmeHelperHN;
};

extern Rva003FD060TerrainLogic *TheTerrainLogic;
extern AI *TheAI;

class BfmeCheckHN
{
public:
	bool bfmeTestHN(BfmeVec3HN *p);

	unsigned char m_bfmeHeadHN[8];
	BfmeObjHN *m_bfme08HN;
};

bool BfmeCheckHN::bfmeTestHN(BfmeVec3HN *p)
{
	BfmeObjHN *o = m_bfme08HN;

	BfmeVec3HN a;

	a.m_bfmeXHN = o->m_bfme38HN;
	a.m_bfmeYHN = o->m_bfme3cHN;
	a.m_bfmeZHN = o->m_bfme40HN;

	BfmeVec3HN b;

	b.m_bfmeXHN = p->m_bfmeXHN;
	b.m_bfmeYHN = p->m_bfmeYHN;
	b.m_bfmeZHN = p->m_bfmeZHN;

	a.m_bfmeZHN = o->m_bfmeGeomHN.getMaxHeightAbovePosition() + a.m_bfmeZHN;

	if (!TheTerrainLogic->bfmeReachHN(&a, &b))
		return false;

	if (TheAI != 0)
	{
		BfmeAiHelperHN *h = TheAI->m_bfmeHelperHN;

		if (h->bfmeBlockedHN(m_bfme08HN, &b))
			return false;
	}

	return true;
}
