// Open-BFME5 conversions.

struct BfmeVecSSA
{
	float m_bfmeX;
	float m_bfmeY;
};

class BfmeCellSSA
{
public:
	BfmeCellSSA *bfmeSetSSA(const BfmeVecSSA *v);
	int m_bfmeX;
	int m_bfmeY;
};

BfmeCellSSA *BfmeCellSSA::bfmeSetSSA(const BfmeVecSSA *v)
{
	m_bfmeX = (int)v->m_bfmeX;
	m_bfmeY = (int)v->m_bfmeY;
	return this;
}
