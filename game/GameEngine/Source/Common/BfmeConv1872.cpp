class BfmeWinZE
{
public:
	virtual void bfmeW0ZE();
	virtual void bfmeW1ZE();
	virtual void bfmeW2ZE();
	virtual void bfmeW3ZE();
	virtual void bfmeW4ZE();
	virtual void bfmeDoneZE();
};

class BfmeManagerZE
{
public:
	virtual void bfmeM00ZE();
	virtual void bfmeM01ZE();
	virtual void bfmeM02ZE();
	virtual void bfmeM03ZE();
	virtual void bfmeM04ZE();
	virtual void bfmeM05ZE();
	virtual void bfmeM06ZE();
	virtual void bfmeM07ZE();
	virtual void bfmeM08ZE();
	virtual void bfmeM09ZE();
	virtual void bfmeM10ZE();
	virtual void bfmeM11ZE();
	virtual void bfmeM12ZE();
	virtual void bfmeM13ZE();
	virtual void bfmeM14ZE();
	virtual void bfmeM15ZE();
	virtual void bfmeM16ZE();
	virtual void bfmeM17ZE();
	virtual void bfmeM18ZE();
	virtual void bfmeM19ZE();
	virtual void bfmeM20ZE();
	virtual void bfmeM21ZE();
	virtual void bfmeM22ZE();
	virtual void bfmeM23ZE();
	virtual void bfmeM24ZE();
	virtual void bfmeM25ZE();
	virtual void bfmeM26ZE();
	virtual void bfmeM27ZE();
	virtual void bfmeM28ZE();
	virtual void bfmeM29ZE();
	virtual void bfmeM30ZE();
	virtual void bfmeM31ZE();
	virtual void bfmeM32ZE();
	virtual void bfmeM33ZE();
	virtual void bfmeM34ZE();
	virtual void bfmeM35ZE();
	virtual void bfmeM36ZE();
	virtual void bfmeM37ZE();
	virtual void bfmeM38ZE();
	virtual void bfmeM39ZE();
	virtual void bfmeM40ZE();
	virtual void bfmeM41ZE();
	virtual void bfmeM42ZE();
	virtual int bfmeBusyZE();
	virtual void bfmeHideZE(BfmeWinZE *win);
};

extern BfmeManagerZE *TheBfmeManagerZE;

char bfmeCheckZE();

class BfmeOwnerZE
{
public:
	void bfmeCloseZE(void *unused);

	unsigned char m_bfmeHeadZE[0x24];
	BfmeWinZE *m_bfmeWinZE;
	char m_bfmeFlagZE;
};

void BfmeOwnerZE::bfmeCloseZE(void *unused)
{
	if (m_bfmeWinZE == 0)
		return;

	if (m_bfmeFlagZE != 0 && TheBfmeManagerZE->bfmeBusyZE() == 0 && bfmeCheckZE() == 0)
		TheBfmeManagerZE->bfmeHideZE(m_bfmeWinZE);

	m_bfmeWinZE->bfmeDoneZE();
}

struct Coord3D
{
	float x;
	float y;
	float z;
};

class GeometryInfo
{
public:
	float getMaxHeightAbovePosition() const;
};

class BfmeOverZC
{
public:
	BfmeOverZC *bfmeWalkZC();

	unsigned char m_bfmeHeadZC[4];
	BfmeOverZC *m_bfme04ZC;
	unsigned char m_bfmeMidZC[0xc0];
	unsigned char m_bfmeC8ZC;
	unsigned char m_bfmeMid2ZC[0x3b9];
	unsigned short m_bfme482ZC;
};

class BfmeSubZC
{
public:
	unsigned char m_bfmeHeadZC[4];
	BfmeOverZC *m_bfme04ZC;
};

class BfmeObjZC
{
public:
	GeometryInfo *bfmeGeomZC();
	Coord3D *bfmePosZC();

	unsigned char m_bfmeHeadZC[4];
	BfmeOverZC *m_bfme04ZC;
	unsigned char m_bfmeMidZC[0xf4];
	BfmeSubZC *m_bfmeFCZC;
};

struct Rva003FD060TerrainLogic
{
	virtual void bfmeV0ZC() = 0;
	virtual void bfmeV1ZC() = 0;
	virtual void bfmeV2ZC() = 0;
	virtual void bfmeV3ZC() = 0;
	virtual void bfmeV4ZC() = 0;
	virtual void bfmeV5ZC() = 0;
	virtual float bfmeGroundZC(float x, float y, void *info) = 0;
};

extern Rva003FD060TerrainLogic *TheTerrainLogic;
extern const float g_bfmeK1266B;
extern const float BfmeZeroRange;

static __forceinline BfmeOverZC *bfmeFinalZC(BfmeOverZC *p)
{
	if (p == 0)
		return 0;

	if (p->m_bfme04ZC == 0)
		return p;

	return p->m_bfme04ZC->bfmeWalkZC();
}

class BfmeHostZC
{
public:
	float bfmeHeightZC();

	unsigned char m_bfmeHeadZC[8];
	BfmeObjZC *m_bfme08ZC;
	unsigned char m_bfmeGapZC[0x22];
	char m_bfme2EZC;
};

float BfmeHostZC::bfmeHeightZC()
{
	BfmeObjZC *o = m_bfme08ZC;
	BfmeOverZC *ov1 = bfmeFinalZC(o->m_bfme04ZC);
	BfmeSubZC *s = o->m_bfmeFCZC;

	if (s != 0 && (bfmeFinalZC(s->m_bfme04ZC)->m_bfmeC8ZC & 0x40) != 0)
		return o->bfmeGeomZC()->getMaxHeightAbovePosition() * g_bfmeK1266B;

	if ((ov1->m_bfme482ZC & 0x386) == 0)
		return BfmeZeroRange;

	if (m_bfme2EZC == 0)
		return BfmeZeroRange;

	Coord3D *p = o->bfmePosZC();
	float coords[3];
	coords[0] = p->x;
	coords[1] = p->y;
	coords[2] = p->z;
	float d = coords[2] - TheTerrainLogic->bfmeGroundZC(coords[0], coords[1], 0);

	return (m_bfme08ZC->bfmeGeomZC()->getMaxHeightAbovePosition() + d) * 2.0f;
}
