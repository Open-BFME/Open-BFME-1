class BfmePairAD
{
public:
	BfmePairAD(int first, float second) { m_bfmeAAD = first; m_bfmeBAD = second; }
	BfmePairAD(const BfmePairAD &other) throw()
	{
		m_bfmeAAD = other.m_bfmeAAD;
		m_bfmeBAD = other.m_bfmeBAD;
	}
	~BfmePairAD();

	int m_bfmeAAD;
	float m_bfmeBAD;
};

// Retail calls ILT 0x00021CEC -> 0x00609BA0, the matched
// BfmeHostESM::bfmeDoESM (BfmeHostESMDo.cpp); the by-value pair keeps the
// copy-constructed temporary shape of the call site.
struct BfmePairESM
{
	BfmePairESM(int first, float second) { m_bfmeAAD = first; m_bfmeBAD = second; }
	BfmePairESM(const BfmePairESM &other) throw()
	{
		m_bfmeAAD = other.m_bfmeAAD;
		m_bfmeBAD = other.m_bfmeBAD;
	}
	~BfmePairESM();

	int m_bfmeAAD;
	float m_bfmeBAD;
};

class BfmeThingESM;

class BfmeHostESM
{
public:
	char bfmeDoESM(BfmeThingESM *thing, BfmePairESM pair, void **out, int one,
		int zero);
};

// Retail global at 0x012F7048 is Rva006092D0State *
// g_rva012F7048LivingWorld (defined once in LivingWorld.cpp).  This TU calls it
// through the local BfmeHostESM view, so the view stays and the global uses
// the canonical spelling.
class Rva006092D0State;
extern Rva006092D0State *g_rva012F7048LivingWorld;

static inline BfmeHostESM *localGlo012F7048(void)
{
	return reinterpret_cast<BfmeHostESM *>(g_rva012F7048LivingWorld);
}

void __stdcall bfmeSendAD(void *first, const BfmePairAD *src)
{
	localGlo012F7048()->bfmeDoESM((BfmeThingESM *)first, BfmePairESM(src->m_bfmeAAD, src->m_bfmeBAD), 0, 1, 1);
}
