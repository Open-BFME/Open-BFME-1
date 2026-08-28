// A row and its extra read out at a place, or everything answered as nothing
// when the place is past the end.

struct BfmeVecOH
{
	int m_bfmeAcross;			// 0x0
	int m_bfmeUp;				// 0x4
	int m_bfmeAlong;			// 0x8
};

class BfmeThingOH
{
public:
	void bfmeGetOH(unsigned int at, BfmeVecOH *out, int *also);

private:
	unsigned char m_bfmeHead[0xcc];		// 0x0cc
	BfmeVecOH *m_bfmeRows;			// 0x0cc
	unsigned char m_bfmeGap[4];		// 0x0d0
	unsigned int m_bfmeCount;		// 0x0d4
	unsigned char m_bfmeGap2[4];		// 0x0d8
	int *m_bfmeAlsos;			// 0x0dc
};

void BfmeThingOH::bfmeGetOH(unsigned int at, BfmeVecOH *out, int *also)
{
	if (at < m_bfmeCount)
	{
		const BfmeVecOH *from = &m_bfmeRows[at];

		out->m_bfmeAcross = from->m_bfmeAcross;
		out->m_bfmeUp = from->m_bfmeUp;
		out->m_bfmeAlong = from->m_bfmeAlong;

		*also = m_bfmeAlsos[at];
	}
	else
	{
		out->m_bfmeAcross = 0;
		out->m_bfmeUp = 0;
		out->m_bfmeAlong = 0;

		*also = 0;
	}
}
