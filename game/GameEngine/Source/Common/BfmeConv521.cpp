struct BfmeVecBTA
{
	int m_bfmeX;
	int m_bfmeY;
	int m_bfmeZ;
};

class BfmeThingBTA
{
public:
	void bfmeStepBTA();
	void bfmeGoBTA(const BfmeVecBTA *src);
	unsigned char m_bfmeHead[8];
	BfmeVecBTA m_bfmeVec;
};

void BfmeThingBTA::bfmeGoBTA(const BfmeVecBTA *src)
{
	m_bfmeVec = *src;
	bfmeStepBTA();
}
