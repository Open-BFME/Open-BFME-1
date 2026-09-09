// ?bfmeParseBE@@YAXPAVINI@@PAX1PBX@Z
// partial score=0.65 date=2026-09-09
extern "C" const char *const _bfmeListBE[];

extern float g_bfmeDefaultBU;

class BFMERetailAsciiString
{
public:
	__forceinline BFMERetailAsciiString() throw() { m_bfmeDataBE = 0; }
	__forceinline ~BFMERetailAsciiString() throw() { releaseBuffer(); }

private:
	void releaseBuffer() throw();

	char *m_bfmeDataBE;
};

class INI
{
public:
	const char *getNextToken(const char *sep) throw();

	static int scanIndexList(const char *s, const char *const *list) throw();
};

struct BfmeFalseBE
{
};

struct BfmeElemBE
{
	void bfmeCopyBE(const BfmeElemBE &o) throw();

	int m_bfme00BE;
	float m_bfme04BE;
	float m_bfme08BE;
	float m_bfme0CBE;
	int m_bfme10BE;
	int m_bfme14BE;
	int m_bfme18BE;
	BFMERetailAsciiString m_bfme1CBE;
	unsigned char m_bfme20BE;
};

class BfmeVecBE
{
public:
	void overflow(BfmeElemBE *p, const BfmeElemBE &e, const BfmeFalseBE &f, unsigned int n, bool b) throw();

	__forceinline void bfmePushBE(const BfmeElemBE &e) throw()
	{
		if (m_bfmeEndBE != m_bfmeCapBE)
		{
			if (m_bfmeEndBE != 0)
				m_bfmeEndBE->bfmeCopyBE(e);

			++m_bfmeEndBE;
		}
		else
		{
			BfmeFalseBE f;

			overflow(m_bfmeEndBE, e, f, 1, true);
		}
	}

	BfmeElemBE *m_bfmeBeginBE;
	BfmeElemBE *m_bfmeEndBE;
	BfmeElemBE *m_bfmeCapBE;
};

class BfmeStoreBE
{
public:
	void bfmeFinishBE() throw();

	unsigned char m_bfmeHeadBE[0x2c];
	BfmeVecBE m_bfme2CBE;
};

void bfmeParseBE(INI *ini, void *instance, void *store, const void *userData)
{
	BfmeElemBE e;

	e.m_bfme00BE = INI::scanIndexList(ini->getNextToken(0), _bfmeListBE);
	e.m_bfme04BE = g_bfmeDefaultBU;
	e.m_bfme08BE = g_bfmeDefaultBU;
	e.m_bfme0CBE = g_bfmeDefaultBU;
	e.m_bfme10BE = 0;
	e.m_bfme14BE = 0;
	e.m_bfme18BE = 0;
	e.m_bfme20BE = 1;

	BfmeStoreBE *o = (BfmeStoreBE *)store;

	o->m_bfme2CBE.bfmePushBE(e);

	o->bfmeFinishBE();
}
