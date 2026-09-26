// ?bfmeSwapCK@BfmeThingCK@@QAEXPAV1@@Z
// partial score=0.55 date=2026-09-09
struct BfmeHandleCK
{
	void *m_bfmePtrCK;
};

void bfmeSwapACK(BfmeHandleCK *a, BfmeHandleCK *b);
void bfmeSwapBCK(void *a, void *b);
void bfmeSwapCCK(void *a, void *b);
void bfmeSwapDCK(BfmeHandleCK *a, BfmeHandleCK *b);

__forceinline void bfmeXchgCK(int &a, int &b)
{
	int t = a;

	a = b;
	b = t;
}

__forceinline void bfmeXchgWCK(short &a, short &b)
{
	short t = a;

	a = b;
	b = t;
}

struct BfmeElemCK
{
	int m_bfme00CK;
	int m_bfme04CK;
	int m_bfme08CK;
	int m_bfme0CCK;
	int m_bfme10CK;
	BfmeHandleCK m_bfme14CK;
};

struct BfmeSubCK
{
	unsigned char m_bfme00CK[4];
	int m_bfme04CK;
	int m_bfme08CK;
	int m_bfme0CCK;
	int m_bfme10CK;
	unsigned char m_bfme14CK[4];
	short m_bfme18CK;
	short m_bfme1ACK;
};

struct BfmeElem3CK
{
	int m_bfme00CK;
	int m_bfme04CK;
	int m_bfme08CK;
	BfmeHandleCK m_bfme0CCK;
	int m_bfme10CK;
	int m_bfme14CK;
	BfmeHandleCK m_bfme18CK;
};

class BfmeThingCK
{
public:
	void bfmeSwapCK(BfmeThingCK *o);

	unsigned char m_bfmeHeadCK[0x28];
	int m_bfme28CK;
	BfmeElemCK m_bfme2CCK[32];
	int m_bfme32CCK;
	BfmeElemCK m_bfme330CK[32];
	BfmeSubCK m_bfme630CK;
	BfmeSubCK m_bfme64CCK;
	unsigned char m_bfme668CK;
	unsigned char m_bfmeGapCK[3];
	BfmeElem3CK m_bfme66CCK[32];
};

void BfmeThingCK::bfmeSwapCK(BfmeThingCK *o)
{
	int i;

	bfmeXchgCK(m_bfme28CK, o->m_bfme28CK);

	for (i = 0; i < 32; i++)
	{
		bfmeXchgCK(m_bfme2CCK[i].m_bfme00CK, o->m_bfme2CCK[i].m_bfme00CK);
		bfmeXchgCK(m_bfme2CCK[i].m_bfme04CK, o->m_bfme2CCK[i].m_bfme04CK);
		bfmeXchgCK(m_bfme2CCK[i].m_bfme08CK, o->m_bfme2CCK[i].m_bfme08CK);
		bfmeXchgCK(m_bfme2CCK[i].m_bfme0CCK, o->m_bfme2CCK[i].m_bfme0CCK);
		bfmeXchgCK(m_bfme2CCK[i].m_bfme10CK, o->m_bfme2CCK[i].m_bfme10CK);

		bfmeSwapACK(&m_bfme2CCK[i].m_bfme14CK, &o->m_bfme2CCK[i].m_bfme14CK);
	}

	bfmeXchgCK(m_bfme32CCK, o->m_bfme32CCK);

	for (i = 0; i < 32; i++)
	{
		bfmeXchgCK(m_bfme330CK[i].m_bfme00CK, o->m_bfme330CK[i].m_bfme00CK);
		bfmeXchgCK(m_bfme330CK[i].m_bfme04CK, o->m_bfme330CK[i].m_bfme04CK);
		bfmeXchgCK(m_bfme330CK[i].m_bfme08CK, o->m_bfme330CK[i].m_bfme08CK);
		bfmeXchgCK(m_bfme330CK[i].m_bfme0CCK, o->m_bfme330CK[i].m_bfme0CCK);
		bfmeXchgCK(m_bfme330CK[i].m_bfme10CK, o->m_bfme330CK[i].m_bfme10CK);

		bfmeSwapACK(&m_bfme330CK[i].m_bfme14CK, &o->m_bfme330CK[i].m_bfme14CK);
	}

	bfmeSwapBCK(&m_bfme630CK, &o->m_bfme630CK);

	bfmeXchgCK(m_bfme630CK.m_bfme04CK, o->m_bfme630CK.m_bfme04CK);
	bfmeXchgCK(m_bfme630CK.m_bfme0CCK, o->m_bfme630CK.m_bfme0CCK);
	bfmeXchgCK(m_bfme630CK.m_bfme10CK, o->m_bfme630CK.m_bfme10CK);

	bfmeSwapCCK(&m_bfme630CK.m_bfme14CK, &o->m_bfme630CK.m_bfme14CK);

	bfmeXchgWCK(m_bfme630CK.m_bfme18CK, o->m_bfme630CK.m_bfme18CK);
	bfmeXchgWCK(m_bfme630CK.m_bfme1ACK, o->m_bfme630CK.m_bfme1ACK);

	bfmeSwapBCK(&m_bfme64CCK, &o->m_bfme64CCK);

	bfmeXchgCK(m_bfme64CCK.m_bfme04CK, o->m_bfme64CCK.m_bfme04CK);
	bfmeXchgCK(m_bfme64CCK.m_bfme0CCK, o->m_bfme64CCK.m_bfme0CCK);
	bfmeXchgCK(m_bfme64CCK.m_bfme10CK, o->m_bfme64CCK.m_bfme10CK);

	bfmeSwapCCK(&m_bfme64CCK.m_bfme14CK, &o->m_bfme64CCK.m_bfme14CK);

	bfmeXchgWCK(m_bfme64CCK.m_bfme18CK, o->m_bfme64CCK.m_bfme18CK);
	bfmeXchgWCK(m_bfme64CCK.m_bfme1ACK, o->m_bfme64CCK.m_bfme1ACK);

	for (i = 0; i < 32; i++)
	{
		bfmeXchgCK(m_bfme66CCK[i].m_bfme00CK, o->m_bfme66CCK[i].m_bfme00CK);
		bfmeXchgCK(m_bfme66CCK[i].m_bfme04CK, o->m_bfme66CCK[i].m_bfme04CK);
		bfmeXchgCK(m_bfme66CCK[i].m_bfme08CK, o->m_bfme66CCK[i].m_bfme08CK);

		bfmeSwapDCK(&m_bfme66CCK[i].m_bfme0CCK, &o->m_bfme66CCK[i].m_bfme0CCK);

		bfmeXchgCK(m_bfme66CCK[i].m_bfme10CK, o->m_bfme66CCK[i].m_bfme10CK);
		bfmeXchgCK(m_bfme66CCK[i].m_bfme14CK, o->m_bfme66CCK[i].m_bfme14CK);

		bfmeSwapDCK(&m_bfme66CCK[i].m_bfme18CK, &o->m_bfme66CCK[i].m_bfme18CK);
	}

	bfmeXchgCK((int &)m_bfme668CK, (int &)o->m_bfme668CK);
}
