// ?bfmeParseBF@@YAXPAVINI@@PAX1PBX@Z
// partial score=0.97 date=2026-09-09
extern "C" const char *const _bfmeListBE[];

class INI
{
public:
	const char *getNextToken(const char *sep) throw();

	static int scanIndexList(const char *s, const char *const *list) throw();
};

struct BfmeElem60
{
	__forceinline BfmeElem60() throw()
	{
		m_bfme00_60 = 0;
		m_bfme04_60 = 1.0f;
		m_bfme08_60 = 1.0f;
		m_bfme0C_60 = 1.0f;
		m_bfme10_60 = 0;
		m_bfme14_60 = 0;
		m_bfme18_60 = 0;
		m_bfme1C_60 = 0;
		m_bfme20_60 = 1;
	}

	__forceinline BfmeElem60(const BfmeElem60 &o) throw()
	{
		m_bfme00_60 = o.m_bfme00_60;
		m_bfme04_60 = o.m_bfme04_60;
		m_bfme08_60 = o.m_bfme08_60;
		m_bfme0C_60 = o.m_bfme0C_60;
		m_bfme10_60 = o.m_bfme10_60;
		m_bfme14_60 = o.m_bfme14_60;
		m_bfme18_60 = o.m_bfme18_60;
		m_bfme1C_60 = o.m_bfme1C_60;
		m_bfme20_60 = o.m_bfme20_60;
	}


	volatile int m_bfme00_60;
	volatile float m_bfme04_60;
	volatile float m_bfme08_60;
	volatile float m_bfme0C_60;
	volatile int m_bfme10_60;
	volatile int m_bfme14_60;
	volatile int m_bfme18_60;
	volatile char *m_bfme1C_60;
	unsigned char m_bfme20_60;
};

class BfmeVec60
{
public:
	void resize(unsigned int n, BfmeElem60 e) throw();

	BfmeElem60 *m_bfmeBegin60;
	BfmeElem60 *m_bfmeEnd60;
	BfmeElem60 *m_bfmeCap60;
};

class BfmeStoreBE
{
public:
	void bfmeFinishBE() throw();

	unsigned char m_bfmeHeadBE[0x2c];
	BfmeVec60 m_bfme2CBE;
};

void bfmeParseBF(INI *ini, void *instance, void *store, const void *userData)
{
	int idx = INI::scanIndexList(ini->getNextToken(0), _bfmeListBE);

	BfmeStoreBE *o = (BfmeStoreBE *)store;

	o->m_bfme2CBE.resize(1, BfmeElem60());

	o->m_bfme2CBE.m_bfmeBegin60->m_bfme00_60 = idx;

	o->bfmeFinishBE();
}
