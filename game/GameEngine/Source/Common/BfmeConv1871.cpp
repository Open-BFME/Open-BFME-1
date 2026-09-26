extern "C" int g_bfmeNameAZC;
extern "C" int g_bfmeNameBZC;
extern "C" void __cdecl bfmeCbAZC();
extern "C" void __cdecl bfmeCbBZC();

class BfmeThingZC
{
public:
	virtual void bfmeV0ZC();
	virtual void bfmeV1ZC();
	virtual void bfmeV2ZC();
	virtual void bfmeSetZC(void *what, int flag);
};

class BfmeHostZC
{
public:
	virtual void bfmeH0ZC();
	virtual void bfmeH1ZC();
	virtual void bfmeH2ZC();
	virtual void bfmeH3ZC();
	virtual void bfmeAddZC(void *name, void *cb, void *owner);

	unsigned char m_bfmeHeadZC[0x6a4];
	BfmeThingZC *m_bfmeThingZC;
};

class BfmeOwnerZC
{
public:
	virtual void bfmeO0ZC();
	virtual BfmeHostZC *bfmeHostZC();

	void bfmeRegisterZC();

	unsigned char m_bfmePadZC[8];
	unsigned char m_bfmeSubZC[4];
};

void BfmeOwnerZC::bfmeRegisterZC()
{
	BfmeHostZC *host = bfmeHostZC();

	host->m_bfmeThingZC->bfmeSetZC(m_bfmeSubZC, 0);

	host->bfmeAddZC(&g_bfmeNameAZC, (void *)bfmeCbAZC, this);
	host->bfmeAddZC(&g_bfmeNameBZC, (void *)bfmeCbBZC, this);
}
