// One more: a triple setter that walks its own base.

class BfmeVecXA
{
public:
	int m_bfmeX;
	int m_bfmeY;
	int m_bfmeZ;
};

class Gen_0026F3C0
{
public:
	void bfmeSetTriple(const BfmeVecXA *src);
private:
	unsigned char m_bfmeGap[0x1d8];				// +0x000
	int m_bfmeKind;								// +0x1d8
	BfmeVecXA m_bfmeVec;						// +0x1dc
};

void Gen_0026F3C0::bfmeSetTriple(const BfmeVecXA *src)
{
	m_bfmeKind = 2;
	m_bfmeVec = *src;
}
