class BfmeSubERF
{
public:
	~BfmeSubERF();

	unsigned char m_bfmeBodyERF[12];
};

struct BfmeItemERF
{
	unsigned char m_bfmeHeadERF[16];
	BfmeSubERF m_bfmeSubERF;
};

class BfmeVecERF
{
public:
	void bfmeResizeERF(unsigned int count, BfmeItemERF value);
	void bfmeEraseERF(BfmeItemERF *first, BfmeItemERF *last);
	void bfmeInsertERF(BfmeItemERF *where, unsigned int count, BfmeItemERF *value);

	BfmeItemERF *m_bfmeFirstERF;
	BfmeItemERF *m_bfmeLastERF;
};

void BfmeVecERF::bfmeResizeERF(unsigned int count, BfmeItemERF value)
{
	if (count < (unsigned int)(m_bfmeLastERF - m_bfmeFirstERF))
		bfmeEraseERF(m_bfmeFirstERF + count, m_bfmeLastERF);
	else
	{
		unsigned int extra =
			count - (unsigned int)(m_bfmeLastERF - m_bfmeFirstERF);

		bfmeInsertERF(m_bfmeLastERF, extra, &value);
	}
}
