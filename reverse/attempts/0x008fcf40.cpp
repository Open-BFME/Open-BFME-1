// ?d_008fcf40@@YAXXZ
// partial score=0.9 date=2026-09-09
void _bfme_debugRecordCallsite(int n);

class BfmeMsgCJ
{
public:
	virtual BfmeMsgCJ *bfmeArgCJ(int v);
	virtual void bfmeV04CJ();
	virtual void bfmeV08CJ();
	virtual void bfmeV0CCJ();
	virtual void bfmeV10CJ();
	virtual void bfmeV14CJ();
	virtual void bfmeV18CJ();
	virtual void bfmeV1CCJ();
	virtual void bfmeV20CJ();
	virtual void bfmeV24CJ();
	virtual void bfmeV28CJ();
	virtual void bfmeV2CCJ();
	virtual void bfmeV30CJ();
	virtual void bfmeV34CJ();
	virtual BfmeMsgCJ *bfmeTextCJ(const char *s);
	virtual void bfmeV3CCJ();
	virtual void bfmeV40CJ();
	virtual void bfmeV44CJ();
	virtual void bfmeV48CJ();
	virtual void bfmeEndCJ(int v);
};

class BfmeAwakenDebug
{
public:
	virtual void bfmeV00CJ();
	virtual void bfmeV04CJ();
	virtual void bfmeV08CJ();
	virtual void bfmeV0CCJ();
	virtual void bfmeV10CJ();
	virtual void bfmeV14CJ();
	virtual void bfmeV18CJ();
	virtual void bfmeV1CCJ();
	virtual void bfmeV20CJ();
	virtual void bfmeV24CJ();
	virtual void bfmeV28CJ();
	virtual void bfmeV2CCJ();
	virtual void bfmeV30CJ();
	virtual void bfmeV34CJ();
	virtual void bfmeV38CJ();
	virtual void bfmeV3CCJ();
	virtual void bfmeV40CJ();
	virtual void bfmeV44CJ();
	virtual void bfmeV48CJ();
	virtual void bfmeV4CCJ();
	virtual void bfmeV50CJ();
	virtual void bfmeV54CJ();
	virtual void bfmeV58CJ();
	virtual void bfmeV5CCJ();
	virtual void bfmeBeginCJ();
	virtual void bfmeV64CJ();
	virtual void bfmeV68CJ();
	virtual BfmeMsgCJ *bfmeOpenCJ(int a, int b);
};

extern BfmeAwakenDebug *TheBfmeAwakenDebug;

struct BfmeDevCJ
{
	void *m_bfmeVftCJ;
};

class SurfaceClass
{
public:
	struct SurfaceDescription
	{
		int m_bfme00CJ;
		int m_bfme04CJ;
		int m_bfme08CJ;
	};

	void Get_Description(SurfaceDescription &d);

	void bfmePokeCJ(int x, int y, int v);

	BfmeDevCJ *volatile m_bfme00CJ;
};

struct BfmeLockCJ
{
	int m_bfme00CJ;
	unsigned char *m_bfme04CJ;
	SurfaceClass::SurfaceDescription m_bfme08CJ;
};

struct BfmeRectCJ
{
	int m_bfmeLCJ;
	int m_bfmeTCJ;
	int m_bfmeRCJ;
	int m_bfmeBCJ;
};

typedef void *(__stdcall *BfmeFn34CJ)(BfmeDevCJ *o, BfmeLockCJ *a, BfmeRectCJ *r, int z);
typedef void *(__stdcall *BfmeFn38CJ)(BfmeDevCJ *o);

void SurfaceClass::bfmePokeCJ(int x, int y, int v)
{
	if (m_bfme00CJ == 0)
		return;

	volatile BfmeRectCJ r;
	volatile BfmeLockCJ a;

	Get_Description((SurfaceDescription &)a.m_bfme08CJ);

	r.m_bfmeLCJ = 0;
	a.m_bfme00CJ = 0;
	r.m_bfmeTCJ = 0;
	a.m_bfme04CJ = 0;
	r.m_bfmeRCJ = 0;
	r.m_bfmeBCJ = 0;

	r.m_bfmeTCJ = y;
	r.m_bfmeBCJ = y + 1;
	r.m_bfmeLCJ = x;
	r.m_bfmeRCJ = x + 1;

	BfmeDevCJ *d = (BfmeDevCJ *)m_bfme00CJ;
	void *p = ((BfmeFn34CJ *)d->m_bfmeVftCJ)[0x34 / 4](d, (BfmeLockCJ *)&a, (BfmeRectCJ *)&r, 0);

	if (p != 0)
	{
		_bfme_debugRecordCallsite(1);

		TheBfmeAwakenDebug->bfmeBeginCJ();
		TheBfmeAwakenDebug->bfmeOpenCJ(0, 0)->bfmeTextCJ("DX8 error ")->bfmeArgCJ((int)p)->bfmeEndCJ(1);
	}

	if (a.m_bfme08CJ.m_bfme00CJ == 0x15)
		a.m_bfme04CJ[3] = (unsigned char)v;

	BfmeDevCJ *e = (BfmeDevCJ *)m_bfme00CJ;
	void *q = ((BfmeFn38CJ *)e->m_bfmeVftCJ)[0x38 / 4](e);

	if (q != 0)
	{
		_bfme_debugRecordCallsite(1);

		TheBfmeAwakenDebug->bfmeBeginCJ();
		TheBfmeAwakenDebug->bfmeOpenCJ(0, 0)->bfmeTextCJ("DX8 error ")->bfmeArgCJ((int)q)->bfmeEndCJ(1);
	}
}
