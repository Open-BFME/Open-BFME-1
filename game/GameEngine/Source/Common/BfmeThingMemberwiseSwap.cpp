// Member-wise swap of a record holding two 32-entry vector-bearing arrays,
// two map-and-vector records, a byte flag and a 32-entry two-vector array.

struct BfmeHandleCK
{
	void *m_bfmePtrCK;
};

struct BfmeSwapTailCJ;
struct BfmeStructuredSwapPart;
class BfmeStructuredSwapRecord;

void __cdecl bfmeSwapTailCJ(BfmeSwapTailCJ *first, BfmeSwapTailCJ *second);
void __cdecl bfmeSwapStructuredHead(BfmeStructuredSwapRecord *left, BfmeStructuredSwapRecord *right);
void __cdecl bfmeSwapStructuredPart(BfmeStructuredSwapPart *left, BfmeStructuredSwapPart *right);
void __cdecl bfmeSwapDCK(BfmeHandleCK *a, BfmeHandleCK *b);

inline void bfmeXchgCK(int &a, int &b)
{
	int t = a;

	a = b;
	b = t;
}

inline void bfmeXchgWCK(short &a, short &b)
{
	short t = a;

	a = b;
	b = t;
}

// Start, finish and end-of-storage words; the last is swapped by the 0x000DE040 proxy swap.
struct BfmeVectorTriple000DE040
{
	int m_start;
	int m_finish;
	BfmeHandleCK m_endOfStorage;

	// ?bfmeSwapCK@BfmeVectorTriple000DE040@@QAEXAAU1@@Z absent-from-retail
	void bfmeSwapCK(BfmeVectorTriple000DE040 &o)
	{
		bfmeXchgCK(m_start, o.m_start);
		bfmeXchgCK(m_finish, o.m_finish);
		bfmeSwapTailCJ(reinterpret_cast<BfmeSwapTailCJ *>(&m_endOfStorage),
			reinterpret_cast<BfmeSwapTailCJ *>(&o.m_endOfStorage));
	}
};

// Start, finish and end-of-storage words; the last is swapped by the 0x00193600 proxy swap.
struct BfmeVectorTriple00193600
{
	int m_start;
	int m_finish;
	BfmeHandleCK m_endOfStorage;

	// ?bfmeSwapCK@BfmeVectorTriple00193600@@QAEXAAU1@@Z absent-from-retail
	void bfmeSwapCK(BfmeVectorTriple00193600 &o)
	{
		bfmeXchgCK(m_start, o.m_start);
		bfmeXchgCK(m_finish, o.m_finish);
		bfmeSwapDCK(&m_endOfStorage, &o.m_endOfStorage);
	}
};

struct BfmeElemCK
{
	int m_bfme00CK;
	int m_bfme04CK;
	int m_bfme08CK;
	BfmeVectorTriple000DE040 m_bfme0CCK;

	// ?bfmeSwapCK@BfmeElemCK@@QAEXAAU1@@Z absent-from-retail
	void bfmeSwapCK(BfmeElemCK &o)
	{
		bfmeXchgCK(m_bfme00CK, o.m_bfme00CK);
		bfmeXchgCK(m_bfme04CK, o.m_bfme04CK);
		bfmeXchgCK(m_bfme08CK, o.m_bfme08CK);
		m_bfme0CCK.bfmeSwapCK(o.m_bfme0CCK);
	}
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

	// ?bfmeSwapCK@BfmeSubCK@@QAEXAAU1@@Z absent-from-retail
	void bfmeSwapCK(BfmeSubCK &o)
	{
		bfmeSwapStructuredHead(reinterpret_cast<BfmeStructuredSwapRecord *>(this),
			reinterpret_cast<BfmeStructuredSwapRecord *>(&o));

		bfmeXchgCK(m_bfme04CK, o.m_bfme04CK);
		bfmeXchgCK(m_bfme0CCK, o.m_bfme0CCK);
		bfmeXchgCK(m_bfme10CK, o.m_bfme10CK);

		bfmeSwapStructuredPart(reinterpret_cast<BfmeStructuredSwapPart *>(m_bfme14CK),
			reinterpret_cast<BfmeStructuredSwapPart *>(o.m_bfme14CK));

		bfmeXchgWCK(m_bfme18CK, o.m_bfme18CK);
		bfmeXchgWCK(m_bfme1ACK, o.m_bfme1ACK);
	}
};

struct BfmeElem3CK
{
	int m_bfme00CK;
	BfmeVectorTriple00193600 m_bfme04CK;
	BfmeVectorTriple00193600 m_bfme10CK;

	// ?bfmeSwapCK@BfmeElem3CK@@QAEXAAU1@@Z absent-from-retail
	void bfmeSwapCK(BfmeElem3CK &o)
	{
		bfmeXchgCK(m_bfme00CK, o.m_bfme00CK);
		m_bfme04CK.bfmeSwapCK(o.m_bfme04CK);
		m_bfme10CK.bfmeSwapCK(o.m_bfme10CK);
	}
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

// ?bfmeSwapCK@BfmeThingCK@@QAEXPAV1@@Z
void BfmeThingCK::bfmeSwapCK(BfmeThingCK *o)
{
	int i;

	bfmeXchgCK(m_bfme28CK, o->m_bfme28CK);
	for (i = 0; i < 32; i++)
		m_bfme2CCK[i].bfmeSwapCK(o->m_bfme2CCK[i]);

	bfmeXchgCK(m_bfme32CCK, o->m_bfme32CCK);
	for (i = 0; i < 32; i++)
		m_bfme330CK[i].bfmeSwapCK(o->m_bfme330CK[i]);

	m_bfme630CK.bfmeSwapCK(o->m_bfme630CK);
	m_bfme64CCK.bfmeSwapCK(o->m_bfme64CCK);

	for (i = 0; i < 32; i++)
		m_bfme66CCK[i].bfmeSwapCK(o->m_bfme66CCK[i]);

	unsigned char t = m_bfme668CK;

	m_bfme668CK = o->m_bfme668CK;
	o->m_bfme668CK = t;
}
