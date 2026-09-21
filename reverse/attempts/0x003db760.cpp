// ??0BfmeCtxYY@@QAE@PAXPAVBfmeObjYY@@PAVBfmeCfgYY@@DD@Z
// partial score=0.97 date=2026-09-08
// pin needed: ?bfmeQueryYY@BfmeObjYY@@QAEDXZ,0x00010EA1
extern "C" void _ReadWriteBarrier();

class LocomotorOverridable
{
public:
	LocomotorOverridable *friend_getFinalOverride();

	unsigned char m_bfmeHeadYY[4];
	LocomotorOverridable *m_bfme04YY;
	unsigned char m_bfmeMidYY[0x43c];
	int m_bfme444YY;
	unsigned char m_bfmeMid2YY[0x84];
	char m_bfme4CCYY;
};

class BfmeObjYY
{
public:
	char bfmeQueryYY();

	unsigned char m_bfmeHeadYY[4];
	LocomotorOverridable *m_bfme04YY;
};

class BfmeCfgYY
{
public:
	unsigned char m_bfmeHeadYY[0x10];
	int m_bfme10YY;
};

static __forceinline LocomotorOverridable *bfmeFinalYY(LocomotorOverridable *p)
{
	if (p == 0)
		return 0;

	if (p->m_bfme04YY == 0)
		return p;

	return p->m_bfme04YY->friend_getFinalOverride();
}

class BfmeCtxYY
{
public:
	BfmeCtxYY(void *a, BfmeObjYY *o, BfmeCfgYY *c, char d, char e);

	void *m_bfme00YY;
	BfmeObjYY *m_bfme04YY;
	BfmeCfgYY *m_bfme08YY;
	int m_bfme0CYY;
	volatile char m_bfme10YY;
	char m_bfme11YY;
	unsigned char m_bfmeGapYY[2];
	volatile int m_bfme14YY;
	char m_bfme18YY;
	volatile char m_bfme19YY;
	char m_bfme1AYY;
	char m_bfme1BYY;
	volatile char m_bfme1CYY;
};

BfmeCtxYY::BfmeCtxYY(void *a, BfmeObjYY *o, BfmeCfgYY *c, char d, char e)
{
	m_bfme00YY = a;
	m_bfme04YY = o;
	m_bfme08YY = c;

	int n = bfmeFinalYY(o->m_bfme04YY)->m_bfme444YY;
	char f = bfmeFinalYY(o->m_bfme04YY)->m_bfme4CCYY;
	char q = o->bfmeQueryYY();
	int cv = c->m_bfme10YY;
	m_bfme11YY = q;
	char dv = d;
	m_bfme0CYY = cv;
	_ReadWriteBarrier();
	char ev = e;
	m_bfme10YY = (f == 0);
	m_bfme14YY = n - 1;
	m_bfme19YY = dv;
	m_bfme18YY = 0;
	m_bfme1AYY = 1;
	m_bfme1BYY = 0;
	m_bfme1CYY = ev;
}
