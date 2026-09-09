// ?bfmeCanZE@BfmeHostZE@@QAEDPAXPAVBfmeObjZE@@@Z
// partial score=0.80 date=2026-09-09
struct BfmeOwnZE
{
	unsigned char m_bfmeHeadZE[0x4b0];
	char m_bfme4B0ZE;
};

class BfmeAgeZE
{
public:
	virtual void bfmeV00ZE();
	virtual void bfmeV04ZE();
	virtual void bfmeV08ZE();
	virtual void bfmeV0CZE();
	virtual void bfmeV10ZE();
	virtual void bfmeV14ZE();
	virtual void bfmeV18ZE();
	virtual void bfmeV1CZE();
	virtual void bfmeV20ZE();
	virtual void bfmeV24ZE();
	virtual void bfmeV28ZE();
	virtual void bfmeV2CZE();
	virtual void bfmeV30ZE();
	virtual void bfmeV34ZE();
	virtual void bfmeV38ZE();
	virtual void bfmeV3CZE();
	virtual unsigned int bfmeAgeZE();
};

class BfmeStateZE
{
public:
	virtual void bfmeW00ZE();
	virtual void bfmeW04ZE();
	virtual void bfmeW08ZE();
	virtual void bfmeW0CZE();
	virtual void bfmeW10ZE();
	virtual void bfmeW14ZE();
	virtual void bfmeW18ZE();
	virtual void bfmeW1CZE();
	virtual void bfmeW20ZE();
	virtual void bfmeW24ZE();
	virtual void bfmeW28ZE();
	virtual void bfmeW2CZE();
	virtual void bfmeW30ZE();
	virtual void bfmeW34ZE();
	virtual void bfmeW38ZE();
	virtual void bfmeW3CZE();
	virtual void bfmeW40ZE();
	virtual void bfmeW44ZE();
	virtual void bfmeW48ZE();
	virtual void bfmeW4CZE();
	virtual void bfmeW50ZE();
	virtual void bfmeW54ZE();
	virtual void bfmeW58ZE();
	virtual void bfmeW5CZE();
	virtual void bfmeW60ZE();
	virtual void bfmeW64ZE();
	virtual int bfmeStateZE();
};

struct Rva00367E30Logic
{
	unsigned char m_bfmeHeadZE[0x3c];
	unsigned int m_bfme3CZE;
};

extern Rva00367E30Logic *TheBfmeGameLogic;

class BfmeObjZE
{
public:
	char bfmeTestZE(int code);
	BfmeOwnZE *bfmeOwnerZE();

	unsigned char m_bfmeHeadZE[0x1fc];
	BfmeStateZE *m_bfme1FCZE;
	BfmeAgeZE *m_bfme200ZE;
	unsigned char m_bfmeMidZE[0x214 - 0x204];
	BfmeObjZE *m_bfme214ZE;
	unsigned char m_bfmeMid2ZE[0x344 - 0x218];
	unsigned char m_bfme344ZE;
};

class BfmeHostZE
{
public:
	char bfmeCanZE(void *a1, BfmeObjZE *obj);
	char bfmeCheckZE(void *a1, BfmeObjZE *obj);
};

char BfmeHostZE::bfmeCanZE(void *a1, BfmeObjZE *obj)
{
	if (obj == 0)
		return 0;

	if (obj->m_bfme344ZE & 1)
	{
		BfmeAgeZE *age = obj->m_bfme200ZE;

		if (age == 0)
			return 0;

		unsigned int limit = TheBfmeGameLogic->m_bfme3CZE;

		if (age->bfmeAgeZE() < limit)
			return 0;
	}

	if (!bfmeCheckZE(a1, obj))
		return 0;

	if (obj->m_bfme1FCZE != 0 && obj->m_bfme1FCZE->bfmeStateZE() != 0)
		return 0;

	if (obj->m_bfme214ZE != 0 && !obj->m_bfme214ZE->bfmeTestZE(0x6c))
		return 0;

	if (obj->bfmeTestZE(0x5d))
		return 0;

	if (obj->bfmeTestZE(7))
		return 0;

	return obj->bfmeOwnerZE()->m_bfme4B0ZE == 0;
}
