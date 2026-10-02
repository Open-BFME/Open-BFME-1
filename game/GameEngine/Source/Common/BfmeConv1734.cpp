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

class Gen_00609320
{
public:
	void bfmeRunAD(void *first, BfmePairAD pair, int a, int b, int c);
};

// Retail global at 0x012F7048 is Rva006092D0State *
// g_rva012F7048LivingWorld (defined once in LivingWorld.cpp).  This TU calls it
// through the local Gen_00609320 view, so the view stays and the global uses
// the canonical spelling.
class Rva006092D0State;
extern Rva006092D0State *g_rva012F7048LivingWorld;

static inline Gen_00609320 *localGlo012F7048(void)
{
	return reinterpret_cast<Gen_00609320 *>(g_rva012F7048LivingWorld);
}

void __stdcall bfmeSendAD(void *first, const BfmePairAD *src)
{
	localGlo012F7048()->bfmeRunAD(first, BfmePairAD(src->m_bfmeAAD, src->m_bfmeBAD), 0, 1, 1);
}
