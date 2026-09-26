// Two more: a five-way read-out and a record copy that takes a reference with
// it.

class Gen_0013CE90
{
public:
	void bfmeFetch(int *a, int *b, int *c, int *d, int *e) const;
private:
	int m_bfmeGap[246];							// +0x000
	int m_bfmeB;								// +0x3d8
	int m_bfmeD;								// +0x3dc
	int m_bfmeGap2[32];							// +0x3e0
	int m_bfmeA;								// +0x460
	int m_bfmeC;								// +0x464
	int m_bfmeE;								// +0x468
};

void Gen_0013CE90::bfmeFetch(int *a, int *b, int *c, int *d, int *e) const
{
	*a = m_bfmeA;
	*b = m_bfmeB;
	*c = m_bfmeC;
	*d = m_bfmeD;
	*e = m_bfmeE;
}

class BfmeThingGF
{
public:
	unsigned short m_bfmeRefs;
};

class BfmeRecGF
{
public:
	unsigned short m_bfmeA;						// +0x00
	unsigned short m_bfmeB;						// +0x02
	unsigned short m_bfmeC;						// +0x04
	unsigned short m_bfmeD;						// +0x06
	int m_bfmeE;								// +0x08
	BfmeThingGF *m_bfmeThing;					// +0x0c
};

void bfmeCopyRec(BfmeRecGF *dst, BfmeRecGF *src)
{
	if (dst == 0)
		return;

	dst->m_bfmeA = src->m_bfmeA;
	dst->m_bfmeB = src->m_bfmeB;
	dst->m_bfmeC = src->m_bfmeC;
	dst->m_bfmeD = src->m_bfmeD;
	dst->m_bfmeE = src->m_bfmeE;

	BfmeThingGF *thing = src->m_bfmeThing;
	dst->m_bfmeThing = thing;
	if (thing != 0)
		++thing->m_bfmeRefs;
}
